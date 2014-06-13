
// @file
// FRED series list - a real treasure trove of data!
// Demonstrates the use of `fredcpp` to:
// - get a list of all series under a given FRED category and its children
//
// The top-most category can also be specified from the command-line.\n
// Some categories may contain no series themselves, only their children categories.\n
// Some series may belong in more than one category.
//
// The retrieved FRED data is written into output file in pipe-delimited format.
//
// @note Expects FRED API key defined in `FRED_API_KEY` enviroment variable.


#include <fredcpp/fredcpp.h>

#include <fredcpp/external/CurlHttpClient.h>
#include <fredcpp/external/PugiXmlParser.h>
#include <fredcpp/external/SimpleLogger.h>

#include <iostream>
#include <cstdlib>
#include <map>
#include <set>
#include <list>


const char* ENV_API_KEY("FRED_API_KEY");
const char* DEFAULT_CATEGORY("18"); // "0" for top-most root category
const char* DEFAULT_OUTPUT_FILE("example.txt");

bool listAllSeries(const std::string& rootCategory, const std::string& outputFile);

bool exitOnApiError(const fredcpp::ApiResponse& response);
bool exitOnBadOutputFile(const std::string& outputFile);
std::string getKeyFromEnv(const std::string& envVar);


typedef std::set<std::string> IdSet;
typedef std::map<std::string, IdSet> ChildrenByIdMap;

std::size_t buildCategoryTree(fredcpp::Api& api, ChildrenByIdMap& tree, const std::string& rootCategory);
std::size_t addCategoryToTree(fredcpp::Api& api, ChildrenByIdMap& tree, const std::string& categoryId);

//______________________________________________________________________________

int main(int argc, char* argv[], char* envp[]) {

  std::string rootCategory(DEFAULT_CATEGORY); 
  std::string outputFile(DEFAULT_OUTPUT_FILE);

  if (argc > 1) {
    rootCategory.assign(argv[1]);
  }

  if (argc > 2) {
    outputFile.assign(argv[2]);
  }

  listAllSeries(rootCategory, outputFile);

  return (0);
}


bool listAllSeries(const std::string& rootCategory, const std::string& outputFile) {
  bool result(false);

  using namespace fredcpp;

  // Initialize

  Api api;
  api.withLogger(external::SimpleLogger::getInstance())
     .withExecutor(external::CurlHttpClient::getInstance())
     .withParser(external::PugiXmlParser::getInstance())
     ;

  external::SimpleLogger::getInstance().enableInfo();

  FREDCPP_LOG_INFO(FREDCPP_FACILITY << " version " << FREDCPP_VERSION_STRING
     << " (" << FREDCPP_BRIEF  << ")");

  FREDCPP_LOG_INFO("Getting API key from environment variable " << ENV_API_KEY << " ...");
  api.withKey(getKeyFromEnv(ENV_API_KEY));


  // Build a list of available sub-categories under the root

  FREDCPP_LOG_INFO("Building list of available sub-categories of category " << rootCategory << " ...");

  ChildrenByIdMap categoryTree;
  if ( 0 == buildCategoryTree(api, categoryTree, rootCategory)) {
    FREDCPP_LOG_FATAL("Unable to retrieve categories");
    exit(EXIT_FAILURE);
  }

  FREDCPP_LOG_INFO("Available categories count:" << categoryTree.size());


  FREDCPP_LOG_INFO("Creating output data file " << outputFile << " ...");
  std::ofstream output(outputFile.c_str());

  if (!output) {
    exitOnBadOutputFile(outputFile);
  }


  // Get series

  IdSet uniqueSeries;
  ApiResponse response;

  for (ChildrenByIdMap::iterator it = categoryTree.begin();
       it != categoryTree.end();
       ++it) {
    std::string categoryId(it->first);

    api.get(ApiRequestBuilder::CategorySeries(categoryId)
            , response) || exitOnApiError(response);

    if (!response.entities.size()) {
      FREDCPP_LOG_INFO("category:" << categoryId << " contains no series");
    }

    // Print series

    // NOTE: a given series can belong to multiple categories,
    // so keep track of unique series

    for (std::size_t n = 0; n < response.entities.size(); ++n) {

      std::string seriesId (response.entities[n].attribute("id"));

      if (uniqueSeries.find(seriesId) != uniqueSeries.end()) {
        continue;
      }

      uniqueSeries.insert(seriesId);

      output << response.entities[n].attribute("id")
             << "|" << response.entities[n].attribute("frequency_short")
             << "|" << response.entities[n].attribute("title")
             << "|" << response.entities[n].attribute("observation_start")
             << "|" << response.entities[n].attribute("observation_end")
             << "|"
             << std::endl;
    }
  }


  // Report stats

  FREDCPP_LOG_INFO("root-category:" << rootCategory
                   << " sub-categories-count:" << categoryTree.size() - 1
                   << " series-count:" << uniqueSeries.size());


  output.close();

  FREDCPP_LOG_INFO("Successfully created file " << outputFile);

  result = true;
  return (result);

}


std::size_t buildCategoryTree(fredcpp::Api& api, ChildrenByIdMap& tree, const std::string& rootCategory) {
  std::size_t categoryCount;

  using namespace fredcpp;

  tree.clear();

  // Request children categories for sub-categories starting from rootCategory

  std::string parentId(rootCategory);


  // Add top-level categories

  categoryCount = addCategoryToTree(api, tree, parentId);

  if (categoryCount == 0) {
    return (categoryCount);
  }

  std::list<IdSet> parentLevels;
  IdSet parents;

  IdSet children = tree[parentId];

  if (children.size()) {
    parentLevels.push_back(children);

  } else {
    return (categoryCount);
  }


  while (parentLevels.size()) {
     parents = parentLevels.front();

    for (IdSet::iterator itNextParent = parents.begin();
         itNextParent != parents.end();
         ++itNextParent) {

      for (IdSet::iterator itChild = children.begin();
           itChild != children.end();
           ++itChild) {
        std::string childId(*itChild);

        //FREDCPP_LOG_INFO("category:" << childId << " parent:" << parentId);

        categoryCount += addCategoryToTree(api, tree,  childId);
      }

      parentId = *itNextParent;
      children = tree[parentId];
      if (children.size()) {
        parentLevels.push_back(children);
      }
    }

    parentLevels.pop_front();
  }

  return (categoryCount);
}


std::size_t addCategoryToTree(fredcpp::Api& api, ChildrenByIdMap& tree, const std::string& categoryId) {
  std::size_t addedCount(0);

  using namespace fredcpp;

  ApiResponse response;
  api.get(ApiRequestBuilder::CategoryChildren(categoryId)
          , response) || exitOnApiError(response);

  // Add categoryId to tree

  std::pair<ChildrenByIdMap::iterator, bool> inserted =
      tree.insert(ChildrenByIdMap::value_type(categoryId, ChildrenByIdMap::mapped_type()));

  if (inserted.second) {
    ++addedCount;
  }

  // Populate category children
  for (std::size_t n = 0; n < response.entities.size(); ++n) {
    std::string childId (response.entities[n].attribute("id"));

    tree[categoryId].insert(childId);
  }

  return (addedCount);
}


bool exitOnApiError(const fredcpp::ApiResponse& response) {
  bool gotError( !response.good() );

  if (gotError) {
    FREDCPP_LOG_ERROR(response.error);

    exit(response.error.status);
  }

  return (gotError);
}


bool exitOnBadOutputFile(const std::string& outputFile) {
  bool gotError(true);

  FREDCPP_LOG_FATAL("Unable to open output file " << outputFile);

  exit(EXIT_FAILURE);

  return (gotError);
}


std::string getKeyFromEnv(const std::string& envVar) {
  const std::string nullKey;

  const char* envKey = envVar.c_str();
  const char* key = std::getenv(envKey);

  if (key == NULL) {
    return (nullKey);
  }

  return (std::string(key));
}
