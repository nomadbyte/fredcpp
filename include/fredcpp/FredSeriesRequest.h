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

#ifndef FREDCPP_FREDSERIESREQUEST_H_
#define FREDCPP_FREDSERIESREQUEST_H_

/// @file
/// Defines FRED series-related requests.


#include <fredcpp/FredEntityRequest.h>


namespace fredcpp {


/// FRED series request with supported parameters.

class FredSeriesRequest : public ApiRequest {
public:
  explicit FredSeriesRequest(const std::string& id = "")
    : ApiRequest("series") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredSeriesRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredSeriesRequest>((*this),"series_id",id));
  }

  FredSeriesRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredSeriesRequest>((*this), date));
  }

  FredSeriesRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredSeriesRequest>((*this), date));
  }

  /// @}

};

//______________________________________________________________________________

/// FRED series observations request with supported parameters.

class FredSeriesObservationsRequest : public ApiRequest {
public:
  explicit FredSeriesObservationsRequest(const std::string& id = "")
    : ApiRequest("series/observations") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredSeriesObservationsRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredSeriesObservationsRequest>((*this),"series_id",id));
  }

  FredSeriesObservationsRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredSeriesObservationsRequest>((*this), date));
  }

  FredSeriesObservationsRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredSeriesObservationsRequest>((*this), date));
  }

  FredSeriesObservationsRequest& withLimit(const std::string& limit){
    return (setLimit<FredSeriesObservationsRequest>((*this), limit));
  }

  FredSeriesObservationsRequest& withOffset(const std::string& offset){
    return (setOffset<FredSeriesObservationsRequest>((*this), offset));
  }

  FredSeriesObservationsRequest& withSort(const std::string& order){
    return (setSort<FredSeriesObservationsRequest>((*this), order));
  }

  FredSeriesObservationsRequest& withOrderBy(const std::string& variable){
    return (setOrderBy<FredSeriesObservationsRequest>((*this), variable));
  }

  FredSeriesObservationsRequest& withStart(const std::string& date) {
    return (setRequestKeyValue<FredSeriesObservationsRequest>((*this),"observation_start", date));
  }

  FredSeriesObservationsRequest& withEnd(const std::string& date) {
    return (setRequestKeyValue<FredSeriesObservationsRequest>((*this),"observation_end", date));
  }

  FredSeriesObservationsRequest& withUnits(const std::string& units) {
    return (setRequestKeyValue<FredSeriesObservationsRequest>((*this),"units", units));
  }

  FredSeriesObservationsRequest& withFrequency(const std::string& frequency) {
    return (setRequestKeyValue<FredSeriesObservationsRequest>((*this),"frequency", frequency));
  }

  FredSeriesObservationsRequest& withAggregation(const std::string& method) {
    return (setRequestKeyValue<FredSeriesObservationsRequest>((*this),"aggregation_method", method));
  }

  FredSeriesObservationsRequest& withOutputType(const std::string& type) {
    return (setRequestKeyValue<FredSeriesObservationsRequest>((*this),"output_type", type));
  }

  FredSeriesObservationsRequest& withFileType(const std::string& type) {
    return (setRequestKeyValue<FredSeriesObservationsRequest>((*this),"file_type", type));
  }

  FredSeriesObservationsRequest& withVintageDates(const std::string& dates) {
    return (setRequestKeyValue<FredSeriesObservationsRequest>((*this),"vintage_dates", dates));
  }

};

//______________________________________________________________________________

/// FRED series release request with supported parameters.

class FredSeriesReleaseRequest : public ApiRequest {
public:
  explicit FredSeriesReleaseRequest(const std::string& id = "")
    : ApiRequest("series/release") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredSeriesReleaseRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredSeriesReleaseRequest>((*this),"series_id",id));
  }


  FredSeriesReleaseRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredSeriesReleaseRequest>((*this), date));
  }

  FredSeriesReleaseRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredSeriesReleaseRequest>((*this), date));
  }

  /// @}

};

//______________________________________________________________________________

/// FRED series categories request with supported parameters.

class FredSeriesCategoriesRequest : public ApiRequest {
public:
  explicit FredSeriesCategoriesRequest(const std::string& id = "")
    : ApiRequest("series/categories") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredSeriesCategoriesRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredSeriesCategoriesRequest>((*this),"series_id",id));
  }


  FredSeriesCategoriesRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredSeriesCategoriesRequest>((*this), date));
  }

  FredSeriesCategoriesRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredSeriesCategoriesRequest>((*this), date));
  }

  /// @}

};

//______________________________________________________________________________

/// FRED series vintage-dates request with supported parameters.

class FredSeriesVintageDatesRequest : public ApiRequest {
public:
  explicit FredSeriesVintageDatesRequest(const std::string& id = "")
    : ApiRequest("series/vintagedates") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredSeriesVintageDatesRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredSeriesVintageDatesRequest>((*this),"series_id",id));
  }

  FredSeriesVintageDatesRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredSeriesVintageDatesRequest>((*this), date));
  }

  FredSeriesVintageDatesRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredSeriesVintageDatesRequest>((*this), date));
  }

  FredSeriesVintageDatesRequest& withLimit(const std::string& limit){
    return (setLimit<FredSeriesVintageDatesRequest>((*this), limit));
  }

  FredSeriesVintageDatesRequest& withOffset(const std::string& offset){
    return (setOffset<FredSeriesVintageDatesRequest>((*this), offset));
  }

  FredSeriesVintageDatesRequest& withSort(const std::string& order){
    return (setSort<FredSeriesVintageDatesRequest>((*this), order));
  }

  /// @}

};


//______________________________________________________________________________

/// FRED series updates request with supported parameters.

class FredSeriesUpdatesRequest : public ApiRequest {
public:
  FredSeriesUpdatesRequest()
    : ApiRequest("series/updates") {
  }

  /// @name Parameters
  /// @{
  FredSeriesUpdatesRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredSeriesUpdatesRequest>((*this), date));
  }

  FredSeriesUpdatesRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredSeriesUpdatesRequest>((*this), date));
  }

  FredSeriesUpdatesRequest& withLimit(const std::string& limit){
    return (setLimit<FredSeriesUpdatesRequest>((*this), limit));
  }

  FredSeriesUpdatesRequest& withOffset(const std::string& offset){
    return (setOffset<FredSeriesUpdatesRequest>((*this), offset));
  }

  FredSeriesUpdatesRequest& withFilter(const std::string& value){
    return (setFilter<FredSeriesUpdatesRequest>((*this), value));
  }

  /// @}

};

//______________________________________________________________________________

/// FRED series search request with supported parameters.

class FredSeriesSearchRequest : public ApiRequest {
public:
  FredSeriesSearchRequest(const std::string& text = "")
    : ApiRequest("series/search") {
    withSearch(text);
  }


  /// @name Parameters
  /// @{
  FredSeriesSearchRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredSeriesSearchRequest>((*this), date));
  }

  FredSeriesSearchRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredSeriesSearchRequest>((*this), date));
  }


  FredSeriesSearchRequest& withLimit(const std::string& limit){
    return (setLimit<FredSeriesSearchRequest>((*this), limit));
  }

  FredSeriesSearchRequest& withOffset(const std::string& offset){
    return (setOffset<FredSeriesSearchRequest>((*this), offset));
  }


  FredSeriesSearchRequest& withSort(const std::string& order){
    return (setSort<FredSeriesSearchRequest>((*this), order));
  }

  FredSeriesSearchRequest& withOrderBy(const std::string& variable){
    return (setOrderBy<FredSeriesSearchRequest>((*this), variable));
  }


  FredSeriesSearchRequest& withFilter(const std::string& value){
    return (setFilter<FredSeriesSearchRequest>((*this), value));
  }

  FredSeriesSearchRequest& withFilterOn(const std::string& variable){
    return (setFilterOn<FredSeriesSearchRequest>((*this), variable));
  }


  FredSeriesSearchRequest& withSearch(const std::string& text) {
    return (setRequestKeyValue<FredSeriesSearchRequest>((*this),"search_text", text));
  }

  FredSeriesSearchRequest& withSearchType(const std::string& type) {
    return (setRequestKeyValue<FredSeriesSearchRequest>((*this),"search_type", type));
  }

  /// @}

};


} // namespace fredcpp

#endif // FREDCPP_FREDSERIESREQUEST_H_
