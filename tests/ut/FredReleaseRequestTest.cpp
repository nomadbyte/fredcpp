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

#include <fredcpp-gtest.h>
#include <gtest/gtest.h>

#include <fredcpp/FredReleaseRequest.h>


// Release

TEST(FredReleaseRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("ReleaseRequest accepts required params");
  using namespace fredcpp;

  FredReleaseRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("release_id"));
}

TEST(FredReleaseRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("ReleaseRequest accepts optional params");
  using namespace fredcpp;

  FredReleaseRequest request;
  request.withId("id")
         .withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         ;

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));
}


// ReleaseSeries

TEST(FredReleaseSeriesRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("ReleaseSeriesRequest accepts required params");
  using namespace fredcpp;

  FredReleaseSeriesRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("release_id"));
}

TEST(FredReleaseSeriesRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("ReleaseSeriesRequest accepts optional params");
  using namespace fredcpp;

  FredReleaseSeriesRequest request;
  request.withId("id")
         .withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         .withLimit("1000")
         .withOffset("0")
         .withSort("asc")
         .withOrderBy("series_id")
         .withFilterOn("frequency")
         .withFilter("d")
         ;

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));

  ASSERT_TRUE(request.hasParam("limit"));
  ASSERT_TRUE(request.hasParam("offset"));

  ASSERT_TRUE(request.hasParam("order_by"));
  ASSERT_TRUE(request.hasParam("sort_order"));

  ASSERT_TRUE(request.hasParam("filter_variable"));
  ASSERT_TRUE(request.hasParam("filter_value"));
}


// ReleaseSources

TEST(FredReleaseSourcesRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("ReleaseSourcesRequest accepts required params");
  using namespace fredcpp;

  FredReleaseSourcesRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("release_id"));
}

TEST(FredReleaseSourcesRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("ReleaseSourcesRequest accepts optional params");
  using namespace fredcpp;

  FredReleaseSourcesRequest request;
  request.withId("id")
         .withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         ;

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));
}


// ReleaseDates

TEST(FredReleaseDatesRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("ReleaseDatesRequest accepts required params");
  using namespace fredcpp;

  FredReleaseDatesRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("release_id"));
}

TEST(FredReleaseDatesRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("ReleaseDatesRequest accepts optional params");
  using namespace fredcpp;

  FredReleaseDatesRequest request;
  request.withId("id")
         .withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         .withLimit("10000")
         .withOffset("0")
         .withSort("asc")
         .withIncludeNoData("false")
         ;

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));

  ASSERT_TRUE(request.hasParam("limit"));
  ASSERT_TRUE(request.hasParam("offset"));

  ASSERT_TRUE(request.hasParam("sort_order"));

  ASSERT_TRUE(request.hasParam("include_release_dates_with_no_data"));
}


// ReleasesDates

TEST(FredReleasesDatesRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("ReleasesDatesRequest accepts optional params");
  using namespace fredcpp;

  FredReleasesDatesRequest request;
  request.withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         .withLimit("1000")
         .withOffset("0")
         .withSort("asc")
         .withOrderBy("release_date")
         .withIncludeNoData("false")
         ;

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));

  ASSERT_TRUE(request.hasParam("limit"));
  ASSERT_TRUE(request.hasParam("offset"));

  ASSERT_TRUE(request.hasParam("order_by"));
  ASSERT_TRUE(request.hasParam("sort_order"));

  ASSERT_TRUE(request.hasParam("include_release_dates_with_no_data"));
}


// Releases

TEST(FredReleasesRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("ReleasesRequest accepts optional params");
  using namespace fredcpp;

  FredReleasesRequest request;
  request.withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         .withLimit("1000")
         .withOffset("0")
         .withSort("asc")
         .withOrderBy("release_id")
         ;

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));

  ASSERT_TRUE(request.hasParam("limit"));
  ASSERT_TRUE(request.hasParam("offset"));

  ASSERT_TRUE(request.hasParam("order_by"));
  ASSERT_TRUE(request.hasParam("sort_order"));
}



