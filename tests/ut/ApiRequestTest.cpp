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

#include <fredcpp/ApiRequestBuilder.h>


// Series

TEST(ApiRequestBuilder, CreatesSeriesPath) {
  FREDCPP_TESTCASE("Series creates a request for 'series' path");
  using namespace fredcpp;

  FredSeriesRequest request = ApiRequestBuilder::Series("TESTID");

  ASSERT_EQ("series", request.getPath());
}


TEST(ApiRequestBuilder, CreatesSeriesObservationsPath) {
  FREDCPP_TESTCASE("SeriesObservations creates a request for 'series/observations' path");
  using namespace fredcpp;

  FredSeriesObservationsRequest request = ApiRequestBuilder::SeriesObservations("TESTID");

  ASSERT_EQ("series/observations", request.getPath());
}


TEST(ApiRequestBuilder, CreatesSeriesReleasePath) {
  FREDCPP_TESTCASE("SeriesRelease creates a request for 'series/release' path");
  using namespace fredcpp;

  FredSeriesReleaseRequest request = ApiRequestBuilder::SeriesRelease("TESTID");

  ASSERT_EQ("series/release", request.getPath());
}


TEST(ApiRequestBuilder, CreatesSeriesCategoriesPath) {
  FREDCPP_TESTCASE("SeriesCategories creates a request for 'series/categories' path");
  using namespace fredcpp;

  FredSeriesCategoriesRequest request = ApiRequestBuilder::SeriesCategories("TESTID");

  ASSERT_EQ("series/categories", request.getPath());
}


TEST(ApiRequestBuilder, CreatesSeriesVintageDatesPath) {
  FREDCPP_TESTCASE("SeriesVintageDates creates a request for 'series/vintagedates' path");
  using namespace fredcpp;

  FredSeriesVintageDatesRequest request = ApiRequestBuilder::SeriesVintageDates("TESTID");

  ASSERT_EQ("series/vintagedates", request.getPath());
}


TEST(ApiRequestBuilder, CreatesSeriesUpdatesPath) {
  FREDCPP_TESTCASE("SeriesUpdates creates a request for 'series/updates' path");
  using namespace fredcpp;

  FredSeriesUpdatesRequest request = ApiRequestBuilder::SeriesUpdates();

  ASSERT_EQ("series/updates", request.getPath());
}


TEST(ApiRequestBuilder, CreatesSeriesSearchPath) {
  FREDCPP_TESTCASE("SeriesSearch creates a request for 'series/search' path");
  using namespace fredcpp;

  FredSeriesSearchRequest request = ApiRequestBuilder::SeriesSearch("TEST TEXT");

  ASSERT_EQ("series/search", request.getPath());
}


// Release

TEST(ApiRequestBuilder, CreatesReleasePath) {
  FREDCPP_TESTCASE("Release creates a request for 'release' path");
  using namespace fredcpp;

  FredReleaseRequest request = ApiRequestBuilder::Release("TESTID");

  ASSERT_EQ("release", request.getPath());
}


TEST(ApiRequestBuilder, CreatesReleaseSeriesPath) {
  FREDCPP_TESTCASE("ReleaseSeries creates a request for 'release/series' path");
  using namespace fredcpp;

  FredReleaseSeriesRequest request = ApiRequestBuilder::ReleaseSeries("TESTID");

  ASSERT_EQ("release/series", request.getPath());
}


TEST(ApiRequestBuilder, CreatesReleaseSourcesPath) {
  FREDCPP_TESTCASE("ReleaseSources creates a request for 'release/sources' path");
  using namespace fredcpp;

  FredReleaseSourcesRequest request = ApiRequestBuilder::ReleaseSources("TESTID");

  ASSERT_EQ("release/sources", request.getPath());
}


TEST(ApiRequestBuilder, CreatesReleaseDatesPath) {
  FREDCPP_TESTCASE("ReleaseDates creates a request for 'release/dates' path");
  using namespace fredcpp;

  FredReleaseDatesRequest request = ApiRequestBuilder::ReleaseDates("TESTID");

  ASSERT_EQ("release/dates", request.getPath());
}


TEST(ApiRequestBuilder, CreatesReleasesDatesPath) {
  FREDCPP_TESTCASE("ReleasesDates creates a request for 'releases/dates' path");
  using namespace fredcpp;

  FredReleasesDatesRequest request = ApiRequestBuilder::ReleasesDates();

  ASSERT_EQ("releases/dates", request.getPath());
}


TEST(ApiRequestBuilder, CreatesReleasesPath) {
  FREDCPP_TESTCASE("Releases creates a request for 'releases' path");
  using namespace fredcpp;

  FredReleasesRequest request = ApiRequestBuilder::Releases();

  ASSERT_EQ("releases", request.getPath());
}


// Source

TEST(ApiRequestBuilder, CreatesSourcePath) {
  FREDCPP_TESTCASE("Source creates a request for 'source' path");
  using namespace fredcpp;

  FredSourceRequest request = ApiRequestBuilder::Source("TESTID");

  ASSERT_EQ("source", request.getPath());
}


TEST(ApiRequestBuilder, CreatesSourceReleasesPath) {
  FREDCPP_TESTCASE("SourceReleases creates a request for 'source/releases' path");
  using namespace fredcpp;

  FredSourceReleasesRequest request = ApiRequestBuilder::SourceReleases("TESTID");

  ASSERT_EQ("source/releases", request.getPath());
}


TEST(ApiRequestBuilder, CreatesSourcesPath) {
  FREDCPP_TESTCASE("Sources creates a request for 'sources' path");
  using namespace fredcpp;

  FredSourcesRequest request = ApiRequestBuilder::Sources();

  ASSERT_EQ("sources", request.getPath());
}


// Category

TEST(ApiRequestBuilder, CreatesCategoryPath) {
  FREDCPP_TESTCASE("Category creates a request for 'category' path");
  using namespace fredcpp;

  FredCategoryRequest request = ApiRequestBuilder::Category("TESTID");

  ASSERT_EQ("category", request.getPath());
}


TEST(ApiRequestBuilder, CreatesCategoryRelatedPath) {
  FREDCPP_TESTCASE("CategoryRelated creates a request for 'category/related' path");
  using namespace fredcpp;

  FredCategoryRelatedRequest request = ApiRequestBuilder::CategoryRelated("TESTID");

  ASSERT_EQ("category/related", request.getPath());
}


TEST(ApiRequestBuilder, CreatesCategorySeriesPath) {
  FREDCPP_TESTCASE("CategorySeries creates a request for 'category/series' path");
  using namespace fredcpp;

  FredCategorySeriesRequest request = ApiRequestBuilder::CategorySeries("TESTID");

  ASSERT_EQ("category/series", request.getPath());
}


TEST(ApiRequestBuilder, CreatesCategoryChildrenPath) {
  FREDCPP_TESTCASE("CategoryChildren creates a request for 'category/children' path");
  using namespace fredcpp;

  FredCategoryChildrenRequest request = ApiRequestBuilder::CategoryChildren("TESTID");

  ASSERT_EQ("category/children", request.getPath());
}


