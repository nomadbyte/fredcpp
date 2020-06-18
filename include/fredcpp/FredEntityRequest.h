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

#ifndef FREDCPP_FREDENTITYREQUEST_H_
#define FREDCPP_FREDENTITYREQUEST_H_

/// @file
/// Defines helper functions to set common FRED request parameters.
/// Used by specific FRED requests.
///
/// @see fredcpp::ApiRequestBuilder


#include <fredcpp/ApiRequest.h>


namespace fredcpp {


/// Set a parameter value.
/// Add a key with non-empty value.

template<typename RequestT>
inline RequestT& setRequestKeyValue(RequestT& request, const std::string& key, const std::string& value) {
  if (!key.empty() && !value.empty()) {
    request.with(key, value);
  }

  return (request);
}


/// @name Realtime
/// @{
template<typename RequestT>
inline RequestT& setRealtimeStart(RequestT& request, const std::string& date) {
  return (setRequestKeyValue<RequestT>(request, "realtime_start", date));
}


template<typename RequestT>
inline RequestT& setRealtimeEnd(RequestT& request, const std::string& date) {
  return (setRequestKeyValue<RequestT>(request, "realtime_end", date));
}
/// @}


/// @name Limit
/// @{
template<typename RequestT>
inline RequestT& setLimit(RequestT& request, const std::string& limit) {
  return (setRequestKeyValue<RequestT>(request, "limit", limit));
}


template<typename RequestT>
inline RequestT& setOffset(RequestT& request, const std::string& offset) {
  return (setRequestKeyValue<RequestT>(request, "offset", offset));
}
/// @}


/// @name Order
/// @{
template<typename RequestT>
inline RequestT& setOrderBy(RequestT& request, const std::string& variable) {
  return (setRequestKeyValue<RequestT>(request, "order_by", variable));
}


template<typename RequestT>
inline RequestT& setSort(RequestT& request, const std::string& order) {
  return (setRequestKeyValue<RequestT>(request, "sort_order", order));
}
/// @}


/// @name Filter
/// @{
template<typename RequestT>
inline RequestT& setFilter(RequestT& request, const std::string& value) {
  return (setRequestKeyValue<RequestT>(request, "filter_value", value));
}


template<typename RequestT>
inline RequestT& setFilterOn(RequestT& request, const std::string& variable) {
  return (setRequestKeyValue<RequestT>(request, "filter_variable", variable));
}
///@}


} // namespace fredcpp

#endif // FREDCPP_FREDENTITYREQUEST_H_
