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

#ifndef FREDCPP_FREDCATEGORYREQUEST_H_
#define FREDCPP_FREDCATEGORYREQUEST_H_

/// @file
/// Defines FRED category-related requests.


#include <fredcpp/FredEntityRequest.h>


namespace fredcpp {

/// FRED category request with supported parameters.

class FredCategoryRequest : public ApiRequest {
public:
  explicit FredCategoryRequest(const std::string& id = "")
    : ApiRequest("category") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredCategoryRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredCategoryRequest>((*this),"category_id",id));
  }

  /// @}

};

//______________________________________________________________________________

/// FRED category related request with supported parameters.

class FredCategoryRelatedRequest : public ApiRequest {
public:
  explicit FredCategoryRelatedRequest(const std::string& id = "")
    : ApiRequest("category/related") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredCategoryRelatedRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredCategoryRelatedRequest>((*this),"category_id",id));
  }

  /// @}

};

//______________________________________________________________________________

/// FRED category series request with supported parameters.

class FredCategorySeriesRequest : public ApiRequest {
public:
  explicit FredCategorySeriesRequest(const std::string& id = "")
    : ApiRequest("category/series") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredCategorySeriesRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredCategorySeriesRequest>((*this),"category_id",id));
  }


  FredCategorySeriesRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredCategorySeriesRequest>((*this), date));
  }

  FredCategorySeriesRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredCategorySeriesRequest>((*this), date));
  }


  FredCategorySeriesRequest& withLimit(const std::string& limit){
    return (setLimit<FredCategorySeriesRequest>((*this), limit));
  }

  FredCategorySeriesRequest& withOffset(const std::string& offset){
    return (setOffset<FredCategorySeriesRequest>((*this), offset));
  }


  FredCategorySeriesRequest& withSort(const std::string& order){
    return (setSort<FredCategorySeriesRequest>((*this), order));
  }

  FredCategorySeriesRequest& withOrderBy(const std::string& variable){
    return (setOrderBy<FredCategorySeriesRequest>((*this), variable));
  }


  FredCategorySeriesRequest& withFilter(const std::string& value){
    return (setFilter<FredCategorySeriesRequest>((*this), value));
  }

  FredCategorySeriesRequest& withFilterOn(const std::string& variable){
    return (setFilterOn<FredCategorySeriesRequest>((*this), variable));
  }

  /// @}

};

//______________________________________________________________________________

/// FRED category children request with supported parameters.

class FredCategoryChildrenRequest : public ApiRequest {
public:
  explicit FredCategoryChildrenRequest(const std::string& id = "")
    : ApiRequest("category/children") {
    withId(id);
  }

  /// @name Parameters
  /// @{
  FredCategoryChildrenRequest& withId(const std::string& id) {
    return (setRequestKeyValue<FredCategoryChildrenRequest>((*this),"category_id",id));
  }


  FredCategoryChildrenRequest& withRealtimeStart(const std::string& date) {
    return (setRealtimeStart<FredCategoryChildrenRequest>((*this), date));
  }

  FredCategoryChildrenRequest& withRealtimeEnd(const std::string& date){
    return (setRealtimeEnd<FredCategoryChildrenRequest>((*this), date));
  }

  /// @}

};

//______________________________________________________________________________


} // namespace fredcpp

#endif // FREDCPP_FREDCATEGORYREQUEST_H_
