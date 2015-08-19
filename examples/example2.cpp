
// @file
// FRED series data file.
// Demonstrates use of `fredcpp` to:
// - get the relevant data for a given FRED series
// - access the retrieved FRED data from the resulting response object
//
// The retrieved FRED data is written to a text file named `<series-id>.txt`,
// where series-id can also be specified from the command-line.
//
// The output file has format __similar__ to FRED series text-files available
// directly from FRED, but used here only for demonstration purposes.
//
// @note Expects FRED API key defined in `FRED_API_KEY` enviroment variable.


#include <fredcpp/fredcpp.h>

#include <fredcpp/external/CurlHttpClient.h>
#include <fredcpp/external/PugiXmlParser.h>
#include <fredcpp/external/SimpleLogger.h>

#include <iostream>
#include <cstdlib>


const char* ENV_API_KEY("FRED_API_KEY");
const char* DEFAULT_SERIES_ID("DEXUSEU");  // Daily USD/EUR Exchange rate

bool createSeriesDataFile(const std::string& seriesId, const std::string& outputFile);

bool exitOnApiError(const fredcpp::ApiResponse& response);
bool exitOnBadOutputFile(const std::string& outputFile);
std::string getKeyFromEnv(const std::string& envVar);


int main(int argc, char* argv[], char* envp[])
{
  std::string seriesId(DEFAULT_SERIES_ID);

  if (argc > 1) {
    seriesId.assign(argv[1]);
  }

  std::string outputFile(seriesId + ".txt");

  createSeriesDataFile(seriesId, outputFile);

  return (0);
}


bool createSeriesDataFile(const std::string& seriesId, const std::string& outputFile) {
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


  // Get series data

  FREDCPP_LOG_INFO("Requesting series " << seriesId << " ...");
  ApiResponse series;
  api.get(ApiRequestBuilder::Series(seriesId)
          , series) || exitOnApiError(series);


  FREDCPP_LOG_INFO("Requesting categories for series " << seriesId << " ...");
  ApiResponse categories;
  api.get(ApiRequestBuilder::SeriesCategories(seriesId)
          , categories) || exitOnApiError(categories);

  FREDCPP_LOG_INFO("Requesting observations for series " << seriesId << " ...");
  ApiResponse observations;
  api.get(ApiRequestBuilder::SeriesObservations(seriesId)
          , observations) || exitOnApiError(observations);

  FREDCPP_LOG_INFO("Requesting release for series " << seriesId << " ...");
  ApiResponse release;
  api.get(ApiRequestBuilder::SeriesRelease(seriesId)
          , release) || exitOnApiError(release);


  std::string releaseId(release.entities[0].attribute("id"));

  FREDCPP_LOG_INFO("Requesting sources for release " << releaseId << " ...");
  ApiResponse sources;
  api.get(ApiRequestBuilder::ReleaseSources(releaseId)
          , sources) || exitOnApiError(sources);


  // Format and output series data
  // Similar format as available from FRED series text-files

  FREDCPP_LOG_INFO("Creating series data file " << outputFile << " ...");
  std::ofstream output(outputFile.c_str());

  if (!output) {
    exitOnBadOutputFile(outputFile);
  }

  // HEADER
  output
    << "Title:               " << series.entities[0].attribute("title") << std::endl
    << "Series ID:           " << series.entities[0].attribute("id") << std::endl
    << "Source:              " << sources.entities[0].attribute("name") << std::endl
    << "Release:             " << release.entities[0].attribute("name") << std::endl
    << "Seasonal Adjustment: " << series.entities[0].attribute("seasonal_adjustment") << std::endl
    << "Frequency:           " << series.entities[0].attribute("frequency") << std::endl
    << "Units:               " << series.entities[0].attribute("units") << std::endl
    << "Date Range:          " << series.entities[0].attribute("observation_start")
                               << " to " << series.entities[0].attribute("observation_end") << std::endl
    << "Last Updated:        " << series.entities[0].attribute("last_updated") << std::endl
    << "Notes:               " << series.entities[0].attribute("notes") << std::endl

    //<< categories.entities[0].attribute("name") << std::endl
    ;
  output << std::endl;


  // OBSERVATIONS

  output << "DATE         VALUE" << std::endl;

  for (std::size_t n = 0; n < observations.entities.size(); ++n) {

    // Skip missing values
    if ( "." == observations.entities[n].attribute("value")) {
      continue;
    }

    output << observations.entities[n].attribute("date")
           << "  " << observations.entities[n].attribute("value")
           << std::endl;
  }


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
