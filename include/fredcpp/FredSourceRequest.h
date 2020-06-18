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

#ifndef FREDCPP_FREDSOURCEREQUEST_H_
#define FREDCPP_FREDSOURCEREQUEST_H_

/// @file
/// Defines FRED source-related requests.


#include <fredcpp/FredEntityRequest.h>


namespace fredcpp {

/// FRED source request with supported parameters.

class FredSourceRequest : public ApiRequest {
public:
  explicit FredSourceRequest(const std::string& id = "")
    : ApiRequest("source") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredSourceRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredSourceRequest>((*this),"source_id",id));
  }

  FredSourceRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredSourceRequest>((*this), date));
  }

  FredSourceRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredSourceRequest>((*this), date));
  }

  /// @}

};


//______________________________________________________________________________

/// FRED source releases request with supported parameters.

class FredSourceReleasesRequest : public ApiRequest {
public:
  explicit FredSourceReleasesRequest(const std::string& id = "")
    : ApiRequest("source/releases") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredSourceReleasesRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredSourceReleasesRequest>((*this),"source_id",id));
  }

  FredSourceReleasesRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredSourceReleasesRequest>((*this), date));
  }

  FredSourceReleasesRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredSourceReleasesRequest>((*this), date));
  }


  FredSourceReleasesRequest& withLimit(const std::string& limit){
    return (setLimit<FredSourceReleasesRequest>((*this), limit));
  }

  FredSourceReleasesRequest& withOffset(const std::string& offset){
    return (setOffset<FredSourceReleasesRequest>((*this), offset));
  }


  FredSourceReleasesRequest& withSort(const std::string& order){
    return (setSort<FredSourceReleasesRequest>((*this), order));
  }

  FredSourceReleasesRequest& withOrderBy(const std::string& variable){
    return (setOrderBy<FredSourceReleasesRequest>((*this), variable));
  }

  /// @}

};

//______________________________________________________________________________

/// FRED sources request with supported parameters.

class FredSourcesRequest : public ApiRequest {
public:
  explicit FredSourcesRequest()
    : ApiRequest("sources") {
  }

  /// @name Parameters
  /// @{
  FredSourcesRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredSourcesRequest>((*this), date));
  }

  FredSourcesRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredSourcesRequest>((*this), date));
  }


  FredSourcesRequest& withLimit(const std::string& limit){
    return (setLimit<FredSourcesRequest>((*this), limit));
  }

  FredSourcesRequest& withOffset(const std::string& offset){
    return (setOffset<FredSourcesRequest>((*this), offset));
  }


  FredSourcesRequest& withSort(const std::string& order){
    return (setSort<FredSourcesRequest>((*this), order));
  }

  FredSourcesRequest& withOrderBy(const std::string& variable){
    return (setOrderBy<FredSourcesRequest>((*this), variable));
  }

  /// @}

};

//______________________________________________________________________________


} // namespace fredcpp

#endif // FREDCPP_FREDSOURCEREQUEST_H_
