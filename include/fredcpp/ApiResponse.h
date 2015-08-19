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

#ifndef FREDCPP_APIRESPONSE_H_
#define FREDCPP_APIRESPONSE_H_

/// @file
/// Defines fredcpp::ApiResponse to store the content returned from FRED API query.
///
/// @example example1.cpp


#include <fredcpp/internal/Request.h>
#include <fredcpp/ApiError.h>

#include <ostream>
#include <vector>
#include <string>


namespace fredcpp {


/// Generic data object returned in FRED API response.
/// Similar to a leaf XML element.
///
/// @note Data members are made public for direct access.\n
/// Use ApiEntity::attribute method to get an attribute's value.
///
/// @see ApiResponse

struct ApiEntity {
  std::string name;
  std::string value;
  internal::KeyValueMap attributes;

  /// Get an attribute value by its name.
  /// When attribute's name is not found, returns an empty value.
  internal::KeyValueMap::mapped_type attribute(const internal::KeyValueMap::key_type& name) const;

  virtual std::ostream& print(std::ostream& os) const;
  virtual void clear();

};

std::ostream& operator<< (std::ostream& os, const ApiEntity& object);

//______________________________________________________________________________


/// Data object to store FRED API query response.
/// Contains data returned from FRED API query or a resulting error.
/// Response is good, when it has no error.
///
/// @note Data members are made public for direct access
///
/// General usage pattern:
/// - passed as an argument to Api::get method call for a FRED request
/// - successful response can be tested with ApiResponse::good() predicate
/// - when good, the result is set and entities are filled with available FRED data
/// - otherwise, error is set
///
/// @see ApiEntity, Api

struct ApiResponse {
  typedef std::vector<ApiEntity> ApiEntityVector;

  ApiEntity result;
  ApiEntityVector entities;
  ApiError error;

  ApiResponse();

  /// Predicate to test whether error is set.
  bool good() const;

  void setError(const ApiError& otherError);
  void setErrorFromResult();

  virtual std::ostream& print(std::ostream& os) const;
  virtual void clear();

};


std::ostream& operator<< (std::ostream& os, const ApiResponse& object);

//______________________________________________________________________________

} // namespace fredcpp

#endif // FREDCPP_APIRESPONSE_H_

