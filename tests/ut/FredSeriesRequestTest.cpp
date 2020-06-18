/*
 *  This file is part of fredcpp library
 *
 *  Copyright (c) 2012 - 2020, Artur Shepilko, <fredcpp@nomadbyte.com>.
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

#include <fredcpp-gtest.h>
#include <gtest/gtest.h>

#include <fredcpp/FredSeriesRequest.h>


// Series

TEST(FredSeriesRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("SeriesRequest accepts required params");
  using namespace fredcpp;

  FredSeriesRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("series_id"));
}

TEST(FredSeriesRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("SeriesRequest accepts optional params");
  using namespace fredcpp;

  FredSeriesRequest request;
  request.withId("id")
         .withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         ;

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));
}


// SeriesObservations

TEST(FredSeriesObservationsRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("SeriesObservationsRequest accepts required params");
  using namespace fredcpp;

  FredSeriesObservationsRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("series_id"));
}

TEST(FredSeriesObservationsRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("SeriesObservationsRequest accepts optional params");
  using namespace fredcpp;

  FredSeriesObservationsRequest request;
  request.withId("id")
         .withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         .withLimit("1000000")
         .withOffset("0")
         .withSort("desc")
         .withOrderBy("observation_date")
         .withStart("1776-07-04")
         .withEnd("9999-12-31")
         .withUnits("lin")
         .withFrequency("d")
         .withAggregation("avg")
         .withOutputType("1")
         .withFileType("xml")
         .withVintageDates("2000-01-01,2000-10-01")
         ;


  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));

  ASSERT_TRUE(request.hasParam("limit"));
  ASSERT_TRUE(request.hasParam("offset"));

  ASSERT_TRUE(request.hasParam("sort_order"));
  ASSERT_TRUE(request.hasParam("order_by"));

  ASSERT_TRUE(request.hasParam("observation_start"));
  ASSERT_TRUE(request.hasParam("observation_end"));

  ASSERT_TRUE(request.hasParam("units"));
  ASSERT_TRUE(request.hasParam("frequency"));
  ASSERT_TRUE(request.hasParam("aggregation_method"));
  ASSERT_TRUE(request.hasParam("output_type"));
  ASSERT_TRUE(request.hasParam("file_type"));
  ASSERT_TRUE(request.hasParam("vintage_dates"));
}


// SeriesRelease

TEST(FredSeriesReleaseRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("SeriesReleaseRequest accepts required params");
  using namespace fredcpp;

  FredSeriesReleaseRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("series_id"));
}

TEST(FredSeriesReleaseRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("SeriesReleaseRequest accepts optional params");
  using namespace fredcpp;

  FredSeriesReleaseRequest request;
  request.withId("id")
         .withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         ;

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));
}


// SeriesCategories

TEST(FredSeriesCategoriesRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("SeriesCategoriesRequest accepts required params");
  using namespace fredcpp;

  FredSeriesCategoriesRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("series_id"));
}

TEST(FredSeriesCategoriesRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("SeriesCategoriesRequest accepts optional params");
  using namespace fredcpp;

  FredSeriesCategoriesRequest request;
  request.withId("id")
         .withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         ;

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));
}


// SeriesVintageDates

TEST(FredSeriesVintageDatesRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("SeriesVintageDatesRequest accepts required params");
  using namespace fredcpp;

  FredSeriesVintageDatesRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("series_id"));
}

TEST(FredSeriesVintageDatesRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("SeriesVintageDatesRequest accepts optional params");
  using namespace fredcpp;

  FredSeriesVintageDatesRequest request;
  request.withId("id")
         .withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         ;

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));
}


// SeriesUpdates

TEST(FredSeriesUpdatesRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("SeriesUpdatesRequest accepts optional params");
  using namespace fredcpp;

  FredSeriesUpdatesRequest request;
  request.withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         .withLimit("100")
         .withOffset("0")
         .withFilter("all")
         ;

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));
  ASSERT_TRUE(request.hasParam("limit"));
  ASSERT_TRUE(request.hasParam("offset"));
  ASSERT_TRUE(request.hasParam("filter_value"));
}


// SeriesSearch

TEST(FredSeriesSearchRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("SeriesSearchRequest accepts required params");
  using namespace fredcpp;

  FredSeriesSearchRequest request;
  request.withSearch("text");


  ASSERT_TRUE(request.hasParam("search_text"));
}

TEST(FredSeriesSearchRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("SeriesSearchRequest accepts optional params");
  using namespace fredcpp;

  FredSeriesSearchRequest request;
  request.withSearch("text")
         .withSearchType("full_text")
         .withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         .withLimit("100")
         .withOffset("0")
         .withOrderBy("search_rank")
         .withSort("desc")
         .withFilterOn("frequency")
         .withFilter("d")
         ;

  ASSERT_TRUE(request.hasParam("search_type"));

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));

  ASSERT_TRUE(request.hasParam("limit"));
  ASSERT_TRUE(request.hasParam("offset"));

  ASSERT_TRUE(request.hasParam("order_by"));
  ASSERT_TRUE(request.hasParam("sort_order"));

  ASSERT_TRUE(request.hasParam("filter_variable"));
  ASSERT_TRUE(request.hasParam("filter_value"));
}
