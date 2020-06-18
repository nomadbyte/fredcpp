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

#include <fredcpp/FredCategoryRequest.h>


// Category

TEST(FredCategoryRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("CategoryRequest accepts required params");
  using namespace fredcpp;

  FredCategoryRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("category_id"));
}


// CategoryRelated

TEST(FredCategoryRelatedRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("CategoryRelatedRequest accepts required params");
  using namespace fredcpp;

  FredCategoryRelatedRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("category_id"));
}


// CategorySeries

TEST(FredCategorySeriesRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("CategorySeriesRequest accepts required params");
  using namespace fredcpp;

  FredCategorySeriesRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("category_id"));
}

TEST(FredCategorySeriesRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("CategorySeriesRequest accepts optional params");
  using namespace fredcpp;

  FredCategorySeriesRequest request;
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


// CategoryChildren

TEST(FredCategoryChildrenRequest, AcceptsRequiredParams) {
  FREDCPP_TESTCASE("CategoryChildrenRequest accepts required params");
  using namespace fredcpp;

  FredCategoryChildrenRequest request;
  request.withId("id");


  ASSERT_TRUE(request.hasParam("category_id"));
}

TEST(FredCategoryChildrenRequest, AcceptsOptionalParams) {
  FREDCPP_TESTCASE("CategoryChildrenRequest accepts optional params");
  using namespace fredcpp;

  FredCategoryChildrenRequest request;
  request.withId("id")
         .withRealtimeStart("2000-01-01")
         .withRealtimeEnd("2000-01-31")
         ;

  ASSERT_TRUE(request.hasParam("realtime_start"));
  ASSERT_TRUE(request.hasParam("realtime_end"));
}
