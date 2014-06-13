/*
 *  This file is part of fredcpp library
 *
 *  Copyright (c) 2012 - 2014, Artur Shepilko, <fredcpp@nomadbyte.com>.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */

#include <fredcpp-testutils.h>

#include <fredcpp-gtest.h>
#include <gtest/gtest.h>

#include <fredcpp/fredcpp.h>

#include <fredcpp/external/CurlHttpClient.h>
#include <fredcpp/external/PugiXmlParser.h>
#include <fredcpp/external/SimpleLogger.h>

#include <fstream>



#define FREDCPP_TEST_APIKEY_FILE "data/api.key"


// Test Fixture

class FredcppTest : public ::testing::Test {
protected:

  virtual void SetUp() {
    if (apiKey.empty()) {
      setApiKey();
    }

    api.withKey(apiKey)
       .withExecutor(fredcpp::external::CurlHttpClient::getInstance())
       .withParser(fredcpp::external::PugiXmlParser::getInstance())
       .withLogger(fredcpp::external::SimpleLogger::getInstance());
  }

  virtual void TearDown() {
  }

  void setApiKey() {
    std::string apiKeyFile(fredcpp::test::harmonizePath(FREDCPP_TEST_APIKEY_FILE));

    std::ifstream ifs(apiKeyFile.c_str());

    assert(ifs && "Valid api.key file expected");

    if (ifs) {
      ifs >> apiKey;
    }
  }


  static std::string apiKey;

  fredcpp::Api api;
  fredcpp::ApiResponse response;
};

std::string FredcppTest::apiKey;

//______________________________________________________________________________

TEST_F(FredcppTest, HttpErrorWhenBadApiUrl) {
  FREDCPP_TESTCASE("Recevies http error when requesting to invalid API url");

  fredcpp::Api badApi("http://api.bad.url/test");
  badApi.withExecutor(fredcpp::external::CurlHttpClient::getInstance())
        .withParser(fredcpp::external::PugiXmlParser::getInstance())
        .withLogger(fredcpp::external::SimpleLogger::getInstance());

  ASSERT_FALSE(badApi.get(fredcpp::ApiRequestBuilder::Series("DEXUSEU"), response));
  ASSERT_EQ(fredcpp::ApiError::FREDCPP_FAIL_HTTP, response.error.status);
  //ASSERT_FALSE(!response.error);
}


TEST_F(FredcppTest, ErrorResponseWhenBadApiKey) {
  FREDCPP_TESTCASE("Recevies error response when passed an invalid API key");

  api.withKey("thisisatestapikey123");

  ASSERT_FALSE(api.get(fredcpp::ApiRequestBuilder::Series("DEXUSEU"), response));
  ASSERT_EQ(fredcpp::ApiError::FREDCPP_ERROR, response.error.status);
  ASSERT_FALSE(!response.error);
  ASSERT_EQ("400", response.error.code);
}


TEST_F(FredcppTest, NonErrorResponseWhenValidRequest) {
  FREDCPP_TESTCASE("Recevies non-error response for a valid API request");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::Series("DEXUSEU"), response));
  ASSERT_EQ(fredcpp::ApiError::FREDCPP_SUCCESS, response.error.status);
  FREDCPP_LOG_INFO("response.error" << response.error);
  ASSERT_TRUE(response.error.code.empty());
  ASSERT_NE("error", response.result.name);
}


TEST_F(FredcppTest, ErrorResponseWhenBadIdValue) {
  FREDCPP_TESTCASE("Recevies error response when requesting with unknown id value");

  ASSERT_FALSE(api.get(fredcpp::ApiRequestBuilder::Series("TESTBADID"), response));
  ASSERT_EQ(fredcpp::ApiError::FREDCPP_ERROR, response.error.status);
  ASSERT_FALSE(!response.error);
  ASSERT_EQ("400", response.error.code);
}


TEST_F(FredcppTest, IgnoresExtraneousRequestParams) {
  FREDCPP_TESTCASE("Recevies valid response when request includes extraneous not-required param");

  fredcpp::FredSeriesReleaseRequest request = fredcpp::ApiRequestBuilder::SeriesRelease("DEXUSEU");

  fredcpp::ApiRequest& badParamRequest = request;

  // This is another reason to use fluent interface, instead of explicit params
  badParamRequest.with("testbadparam", "value");

  ASSERT_TRUE(api.get(badParamRequest, response));
  ASSERT_TRUE(!response.error);
}

//______________________________________________________________________________

// Series

TEST_F(FredcppTest, ValidSeriesResponse) {
  FREDCPP_TESTCASE("Series response contains 'seriess' result of [single] 'series' entities for the requested id");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::Series("DEXUSEU"), response));

  ASSERT_EQ("seriess", response.result.name);
  ASSERT_EQ(1U, response.entities.size());
  ASSERT_EQ("series", response.entities[0].name);
  ASSERT_EQ("DEXUSEU", response.entities[0].attribute("id"));
}


TEST_F(FredcppTest, ValidSeriesObservationsResponse) {
  FREDCPP_TESTCASE("SeriesObservations response contains 'observations' result of 'observation' entities");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::SeriesObservations("DEXUSEU")
      , response));

  ASSERT_EQ("observations", response.result.name);
  ASSERT_GE(response.entities.size(), 1U);
  ASSERT_EQ("observation", response.entities[0].name);
}


TEST_F(FredcppTest, ValidSeriesObservationsWithLimitResponse) {
  FREDCPP_TESTCASE("SeriesObservations response contains 'observations' result of limit# 'observation' entities");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::SeriesObservations("DEXUSEU")
      .withLimit("3")
      , response));

  ASSERT_EQ("observations", response.result.name);
  ASSERT_EQ(response.entities.size(), 3U); // limit
  ASSERT_EQ("observation", response.entities[0].name);
}


TEST_F(FredcppTest, ValidSeriesObservationsWithOffsetResponse) {
  FREDCPP_TESTCASE("SeriesObservations response contains 'observations' result with requested offset");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::SeriesObservations("DEXUSEU")
      .withOffset("5")
      , response));

  ASSERT_EQ("observations", response.result.name);
  ASSERT_EQ(response.result.attribute("offset"), "5"); // offset
}


TEST_F(FredcppTest, ValidSeriesObservationsWithSortResponse) {
  FREDCPP_TESTCASE("SeriesObservations response contains 'observations' result sorted as requested");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::SeriesObservations("DEXUSEU")
      .withSort("desc")
      .withLimit("3")
      , response));

  ASSERT_EQ("observations", response.result.name);
  ASSERT_EQ(response.result.attribute("sort_order"), "desc");
}


TEST_F(FredcppTest, ValidSeriesUpdatesResponse) {
  FREDCPP_TESTCASE("SeriesUpdates response contains 'seriess' result of 'series' entities");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::SeriesUpdates()
      .withLimit("3")
      , response));

  ASSERT_EQ("seriess", response.result.name);
  ASSERT_EQ(response.entities.size(), 3U); // limit
  ASSERT_EQ("series", response.entities[0].name);
}


TEST_F(FredcppTest, ValidSeriesUpdatesWithFilterResponse) {
  FREDCPP_TESTCASE("SeriesUpdates response contains 'seriess' result with requested filter value");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::SeriesUpdates()
      .withLimit("3")
      .withFilter("macro")
      , response));

  ASSERT_EQ("seriess", response.result.name);
  ASSERT_EQ("macro", response.result.attribute("filter_value"));
}


TEST_F(FredcppTest, ValidSeriesVintageDatesResponse) {
  FREDCPP_TESTCASE("SeriesVintageDates response contains 'vintage_dates' result of 'vintage_date' entities for the requested id");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::SeriesVintageDates("DEXUSEU")
      .withLimit("3")
      , response));

  ASSERT_EQ("vintage_dates", response.result.name);
  ASSERT_EQ(response.entities.size(), 3U); // limit
  ASSERT_EQ("vintage_date", response.entities[0].name);
  ASSERT_FALSE(response.entities[0].value.empty()); // non-empty date value
}


TEST_F(FredcppTest, ValidSeriesSearchResponse) {
  FREDCPP_TESTCASE("SeriesSearch response contains 'seriess' result of 'series' entities matching text");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::SeriesSearch("money stock")
      .withLimit("3")
      , response));

  ASSERT_EQ("seriess", response.result.name);
  ASSERT_EQ(response.entities.size(), 3U); // limit
  ASSERT_EQ("series", response.entities[0].name);
}


TEST_F(FredcppTest, ErrorWhenRealtimeEndAfterLastSeriesVintageDates) {
  FREDCPP_TESTCASE("Error response for SeriesVintageDates, when realtime-end is after last available vintage data for id."
                   "\nNOTE: This test is currently failing due to error 500:InternalError returned instead of expected 400."
  );

  // SETUP: get realtimeStart date to setup the test condition
  std::string realtimeStart;

  // get recent vintage for DEXUSEU (D-daily)
  if (api.get(fredcpp::ApiRequestBuilder::SeriesVintageDates("DEXUSEU")
        .withSort("desc")
        .withLimit("1")
        , response)) {

      std::string recentDaily(response.entities[0].value);

      // get recent vintage date for AEXUSEU (A-annual)
      std::string recentAnnual;

      if (api.get(fredcpp::ApiRequestBuilder::SeriesVintageDates("AEXUSEU")
            .withSort("desc")
            .withLimit("1")
            , response)) {

          recentAnnual = response.entities[0].value;
      }

    // expect recent Daily be after recent Annual vintage date
    // so can use the Daily vintage for realtimeStart
    if (recentAnnual < recentDaily) {
      realtimeStart = recentDaily;
    }
  }

  if (realtimeStart.empty()) {
    return; // SKIPTEST:cannot setup the condition (assume passed)
  }


  // TEST: Request Annual item with realtime-start _after_ its last available vintage date

  ASSERT_FALSE(api.get(fredcpp::ApiRequestBuilder::SeriesVintageDates("AEXUSEU")
        .withRealtimeStart(realtimeStart)
        .withLimit("1")
        , response));
  ASSERT_EQ(fredcpp::ApiError::FREDCPP_ERROR, response.error.status);
  ASSERT_FALSE(!response.error);
  EXPECT_EQ("400", response.error.code); // Bad request
}

//______________________________________________________________________________

// Release

TEST_F(FredcppTest, ValidReleaseResponse) {
  FREDCPP_TESTCASE("Release response contains 'releases' result of [single] 'release' entities for the requested id");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::Release("17"), response));

  ASSERT_EQ("releases", response.result.name);
  ASSERT_EQ(1U, response.entities.size());
  ASSERT_EQ("release", response.entities[0].name);
  ASSERT_EQ("17", response.entities[0].attribute("id"));
}


TEST_F(FredcppTest, ValidReleasesResponse) {
  FREDCPP_TESTCASE("Releases response contains 'releases' result of 'release' entities");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::Releases()
        .withLimit("3"), response));

  ASSERT_EQ("releases", response.result.name);
  ASSERT_LE(response.entities.size(), 3U);
  ASSERT_EQ("release", response.entities[0].name);
}

//______________________________________________________________________________

// Source

TEST_F(FredcppTest, ValidSourceResponse) {
  FREDCPP_TESTCASE("Source response contains 'sources' result of [single] 'source' entities for the requested id");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::Source("1"), response));

  ASSERT_EQ("sources", response.result.name);
  ASSERT_EQ(1U, response.entities.size());
  ASSERT_EQ("source", response.entities[0].name);
  ASSERT_EQ("1", response.entities[0].attribute("id"));
}


TEST_F(FredcppTest, ValidSourcesResponse) {
  FREDCPP_TESTCASE("Sources response contains 'sources' result of 'source' entities");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::Sources()
        .withLimit("3"), response));

  ASSERT_EQ("sources", response.result.name);
  ASSERT_LE(response.entities.size(), 3U);
  ASSERT_EQ("source", response.entities[0].name);
}

//______________________________________________________________________________

// Category

TEST_F(FredcppTest, ValidCategoryResponse) {
  FREDCPP_TESTCASE("Category response contains 'categories' result of [single] 'category' entities for the requested id");

  ASSERT_TRUE(api.get(fredcpp::ApiRequestBuilder::Category("94"), response));

  ASSERT_EQ("categories", response.result.name);
  ASSERT_EQ(1U, response.entities.size());
  ASSERT_EQ("category", response.entities[0].name);
  ASSERT_EQ("94", response.entities[0].attribute("id"));
}


