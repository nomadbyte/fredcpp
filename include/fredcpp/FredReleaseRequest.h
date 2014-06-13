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

#ifndef FREDCPP_FREDRELEASEREQUEST_H_
#define FREDCPP_FREDRELEASEREQUEST_H_

/// @file
/// Defines FRED release-related requests.


#include <fredcpp/FredEntityRequest.h>


namespace fredcpp {

/// FRED release request with supported parameters.

class FredReleaseRequest : public ApiRequest {
public:
  explicit FredReleaseRequest(const std::string& id = "")
    : ApiRequest("release") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredReleaseRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredReleaseRequest>((*this),"release_id",id));
  }

  FredReleaseRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredReleaseRequest>((*this), date));
  }

  FredReleaseRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredReleaseRequest>((*this), date));
  }

  /// @}

};

//______________________________________________________________________________

/// FRED release series request with supported parameters.

class FredReleaseSeriesRequest : public ApiRequest {
public:
  explicit FredReleaseSeriesRequest(const std::string& id = "")
    : ApiRequest("release/series") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredReleaseSeriesRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredReleaseSeriesRequest>((*this),"release_id",id));
  }


  FredReleaseSeriesRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredReleaseSeriesRequest>((*this), date));
  }

  FredReleaseSeriesRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredReleaseSeriesRequest>((*this), date));
  }


  FredReleaseSeriesRequest& withLimit(const std::string& limit){
    return (setLimit<FredReleaseSeriesRequest>((*this), limit));
  }

  FredReleaseSeriesRequest& withOffset(const std::string& offset){
    return (setOffset<FredReleaseSeriesRequest>((*this), offset));
  }


  FredReleaseSeriesRequest& withSort(const std::string& order){
    return (setSort<FredReleaseSeriesRequest>((*this), order));
  }

  FredReleaseSeriesRequest& withOrderBy(const std::string& variable){
    return (setOrderBy<FredReleaseSeriesRequest>((*this), variable));
  }


  FredReleaseSeriesRequest& withFilter(const std::string& value){
    return (setFilter<FredReleaseSeriesRequest>((*this), value));
  }

  FredReleaseSeriesRequest& withFilterOn(const std::string& variable){
    return (setFilterOn<FredReleaseSeriesRequest>((*this), variable));
  }

  /// @}

};

//______________________________________________________________________________

/// FRED release sources request with supported parameters.

class FredReleaseSourcesRequest : public ApiRequest {
public:
  explicit FredReleaseSourcesRequest(const std::string& id = "")
    : ApiRequest("release/sources") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredReleaseSourcesRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredReleaseSourcesRequest>((*this),"release_id",id));
  }

  FredReleaseSourcesRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredReleaseSourcesRequest>((*this), date));
  }

  FredReleaseSourcesRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredReleaseSourcesRequest>((*this), date));
  }

  /// @}

};

//______________________________________________________________________________

/// FRED release dates request with supported parameters.

class FredReleaseDatesRequest : public ApiRequest {
public:
  explicit FredReleaseDatesRequest(const std::string& id = "")
    : ApiRequest("release/dates") {
    withId(id);
  }

  FredReleaseDatesRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredReleaseDatesRequest>((*this),"release_id",id));
  }


  FredReleaseDatesRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredReleaseDatesRequest>((*this), date));
  }

  FredReleaseDatesRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredReleaseDatesRequest>((*this), date));
  }


  FredReleaseDatesRequest& withLimit(const std::string& limit){
    return (setLimit<FredReleaseDatesRequest>((*this), limit));
  }

  FredReleaseDatesRequest& withOffset(const std::string& offset){
    return (setOffset<FredReleaseDatesRequest>((*this), offset));
  }


  FredReleaseDatesRequest& withSort(const std::string& order){
    return (setSort<FredReleaseDatesRequest>((*this), order));
  }


  FredReleaseDatesRequest& withIncludeNoData(const std::string& value){
    return (setRequestKeyValue<FredReleaseDatesRequest>((*this), "include_release_dates_with_no_data", value));
  }

  /// @}

};

//______________________________________________________________________________

/// FRED releases dates request with supported parameters.

class FredReleasesDatesRequest : public ApiRequest {
public:
  explicit FredReleasesDatesRequest()
    : ApiRequest("releases/dates") {
  }

  /// @name Parameters
  /// @{
  FredReleasesDatesRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredReleasesDatesRequest>((*this), date));
  }

  FredReleasesDatesRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredReleasesDatesRequest>((*this), date));
  }


  FredReleasesDatesRequest& withLimit(const std::string& limit){
    return (setLimit<FredReleasesDatesRequest>((*this), limit));
  }

  FredReleasesDatesRequest& withOffset(const std::string& offset){
    return (setOffset<FredReleasesDatesRequest>((*this), offset));
  }


  FredReleasesDatesRequest& withSort(const std::string& order){
    return (setSort<FredReleasesDatesRequest>((*this), order));
  }

  FredReleasesDatesRequest& withOrderBy(const std::string& variable){
    return (setOrderBy<FredReleasesDatesRequest>((*this), variable));
  }


  FredReleasesDatesRequest& withIncludeNoData(const std::string& value){
    return (setRequestKeyValue<FredReleasesDatesRequest>((*this), "include_release_dates_with_no_data", value));
  }

};

//______________________________________________________________________________

/// FRED releases request with supported parameters.

class FredReleasesRequest : public ApiRequest {
public:
  explicit FredReleasesRequest()
    : ApiRequest("releases") {
  }


  /// @name Parameters
  /// @{
  FredReleasesRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredReleasesRequest>((*this), date));
  }

  FredReleasesRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredReleasesRequest>((*this), date));
  }


  FredReleasesRequest& withLimit(const std::string& limit){
    return (setLimit<FredReleasesRequest>((*this), limit));
  }

  FredReleasesRequest& withOffset(const std::string& offset){
    return (setOffset<FredReleasesRequest>((*this), offset));
  }


  FredReleasesRequest& withSort(const std::string& order){
    return (setSort<FredReleasesRequest>((*this), order));
  }

  FredReleasesRequest& withOrderBy(const std::string& variable){
    return (setOrderBy<FredReleasesRequest>((*this), variable));
  }

  /// @}

};

//______________________________________________________________________________

} // namespace fredcpp

#endif // FREDCPP_FREDRELEASEREQUEST_H_
