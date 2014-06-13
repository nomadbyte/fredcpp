
// @file
// FRED series updates.
// Demonstrates the use of `fredcpp` to:
// - request FRED category information
// - get a list of recently updated series for a given FRED category
// - get observations for a given FRED series
//
// The retrieved FRED data is written into output file.
//
// @note Expects FRED API key defined in `FRED_API_KEY` enviroment variable.


#include <fredcpp/fredcpp.h>

#include <fredcpp/external/CurlHttpClient.h>
#include <fredcpp/external/PugiXmlParser.h>
#include <fredcpp/external/SimpleLogger.h>

#include <iostream>


const char* ENV_API_KEY("FRED_API_KEY");
const char* DEFAULT_OUTPUT_FILE("example.txt");

bool getSeriesUpdates(const std::string& outputFile);

bool exitOnApiError(const fredcpp::ApiResponse& response);
bool exitOnBadOutputFile(const std::string& outputFile);
std::string getKeyFromEnv(const std::string& envVar);


int main(int argc, char* argv[], char* envp[])
{
  std::string outputFile(DEFAULT_OUTPUT_FILE);


  if (argc > 1) {
    outputFile.assign(argv[1]);
  }

  getSeriesUpdates(outputFile);

  return (0);
}


bool getSeriesUpdates(const std::string& outputFile) {
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


  FREDCPP_LOG_INFO("Creating output data file " << outputFile << " ...");
  std::ofstream output(outputFile.c_str());

  if (!output) {
    exitOnBadOutputFile(outputFile);
  }

  // Request data
  ApiResponse response;


  // Get Category 18: National Income & Product Accounts

  FREDCPP_LOG_INFO("Requesting category 18 ...");

  api.get(ApiRequestBuilder::Category("18")
          , response) || exitOnApiError(response);

  output << response;


  // Get children categories for category 18: National Income & Product Accounts

  FREDCPP_LOG_INFO("Requesting sub-categories of category "
          << response.entities[0].attribute("id")
          << "|" << response.entities[0].attribute("name"));

  api.get(ApiRequestBuilder::CategoryChildren(response.entities[0].attribute("id"))
          , response) || exitOnApiError(response);

  output << response;


  // Get the 10 most recently updated quarterly FRED series
  // in category 106: National Income & Product Accounts > GDP/GNP

  FREDCPP_LOG_INFO("Requesting 10 most recently updated quarterly series in category 106 ...");

  api.get(ApiRequestBuilder::CategorySeries("106")
          .withOrderBy("last_updated")
          .withSort("desc")
          .withLimit("10")
          .withFilterOn("frequency")
          .withFilter("Quarterly")
          , response) || exitOnApiError(response);

  output << response;


  // Get series CBIC1: Real Change in Private Inventories, 1 Decimal

  FREDCPP_LOG_INFO("Requesting series CBIC1 ...");

  api.get(ApiRequestBuilder::Series("CBIC1")
          , response) || exitOnApiError(response);

  output << response;


  // Get observations for series CBIC1: Real Change in Private Inventories, 1 Decimal

  FREDCPP_LOG_INFO("Requesting observations for series "
        << response.entities[0].attribute("id")
        << "|" << response.entities[0].attribute("title"));

  api.get(ApiRequestBuilder::SeriesObservations("CBIC1")
          , response) || exitOnApiError(response);

  output << response;


  output.close();

  FREDCPP_LOG_INFO("Successfully created file " << outputFile);


  result = true;
  return (result);
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
