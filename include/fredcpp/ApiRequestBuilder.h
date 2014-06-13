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

#ifndef FREDCPP_APIREQUESTBUILDER_H_
#define FREDCPP_APIREQUESTBUILDER_H_

/// @file
/// Defines fredcpp::ApiRequestBuilder class,
/// to facilitate generation of supported FRED API requests.
///
/// @example example1.cpp


#include <fredcpp/FredSeriesRequest.h>
#include <fredcpp/FredReleaseRequest.h>
#include <fredcpp/FredSourceRequest.h>
#include <fredcpp/FredCategoryRequest.h>

#include <string>


namespace fredcpp {

namespace builder {

template<typename RequestT>
inline static RequestT makeRequest() {
  RequestT request;
  return (request);
}

template<typename RequestT>
inline static RequestT makeRequest(const std::string& id) {
  RequestT request;
  request.withId(id);
  return (request);
}


// SeriesSearch

template<>
inline FredSeriesSearchRequest makeRequest(const std::string& text) {
  FredSeriesSearchRequest request;
  request.withSearch(text);
  return (request);
}

} // namespace builder



/// Helper class to generate a specific FRED API request instance.
/// Defines a static interface that returns an instance of supported FRED API requests.
///
/// General usage pattern:
/// - use inline as argument on call to Api::get method
/// - generate a specific API request object by calling the corresponding static method
/// - configure the resulting request object with supported parameters
/// - alternatively, assign the resulting request to an explicitly declared specific request object

class ApiRequestBuilder {
public:
  /// @name Series Requests
  /// Build FRED series-related requests.
  /// @{
  static FredSeriesRequest Series(const std::string& id) {
    return (builder::makeRequest<FredSeriesRequest>(id));
  }

  static FredSeriesObservationsRequest SeriesObservations(const std::string& id) {
    return (builder::makeRequest<FredSeriesObservationsRequest>(id));
  }

  static FredSeriesReleaseRequest SeriesRelease(const std::string& id) {
    return (builder::makeRequest<FredSeriesReleaseRequest>(id));
  }

  static FredSeriesCategoriesRequest SeriesCategories(const std::string& id) {
    return (builder::makeRequest<FredSeriesCategoriesRequest>(id));
  }

  static FredSeriesVintageDatesRequest SeriesVintageDates(const std::string& id) {
    return (builder::makeRequest<FredSeriesVintageDatesRequest>(id));
  }

  static FredSeriesUpdatesRequest SeriesUpdates() {
    return (builder::makeRequest<FredSeriesUpdatesRequest>());
  }

  static FredSeriesSearchRequest SeriesSearch(const std::string& text) {
    return (builder::makeRequest<FredSeriesSearchRequest>(text));
  }
  /// @}


  /// @name Release Requests
  /// Build FRED release-related requests.
  /// @{
  static FredReleaseRequest Release(const std::string& id) {
    return (builder::makeRequest<FredReleaseRequest>(id));
  }

  static FredReleaseSeriesRequest ReleaseSeries(const std::string& id) {
    return (builder::makeRequest<FredReleaseSeriesRequest>(id));
  }

  static FredReleaseSourcesRequest ReleaseSources(const std::string& id) {
    return (builder::makeRequest<FredReleaseSourcesRequest>(id));
  }

  static FredReleaseDatesRequest ReleaseDates(const std::string& id) {
    return (builder::makeRequest<FredReleaseDatesRequest>(id));
  }

  static FredReleasesDatesRequest ReleasesDates() {
    return (builder::makeRequest<FredReleasesDatesRequest>());
  }

  static FredReleasesRequest Releases() {
    return (builder::makeRequest<FredReleasesRequest>());
  }
  /// @}


  /// @name Source Requests
  /// Build FRED source-related requests.
  /// @{
  static FredSourceRequest Source(const std::string& id) {
    return (builder::makeRequest<FredSourceRequest>(id));
  }

  static FredSourceReleasesRequest SourceReleases(const std::string& id) {
    return (builder::makeRequest<FredSourceReleasesRequest>(id));
  }

  static FredSourcesRequest Sources() {
    return (builder::makeRequest<FredSourcesRequest>());
  }
  /// @}


  /// @name Category Requests
  /// Build FRED category-related requests.
  /// @{
  static FredCategoryRequest Category(const std::string& id) {
    return (builder::makeRequest<FredCategoryRequest>(id));
  }

  static FredCategoryRelatedRequest CategoryRelated(const std::string& id) {
    return (builder::makeRequest<FredCategoryRelatedRequest>(id));
  }

  static FredCategorySeriesRequest CategorySeries(const std::string& id) {
    return (builder::makeRequest<FredCategorySeriesRequest>(id));
  }

  static FredCategoryChildrenRequest CategoryChildren(const std::string& id) {
    return (builder::makeRequest<FredCategoryChildrenRequest>(id));
  }
  /// @}


protected:
  explicit ApiRequestBuilder();
  virtual ~ApiRequestBuilder();

};

} // namespace fredcpp


#endif // FREDCPP_APIREQUESTBUILDER_H_
