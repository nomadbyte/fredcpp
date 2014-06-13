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

#ifndef FREDCPP_APIERROR_H_
#define FREDCPP_APIERROR_H_

/// @file
/// Defines fredcpp::ApiError, error status, and derived specific errors.
///
/// @example example1.cpp


#include <ostream>
#include <string>

namespace fredcpp {

/// `fredcpp` error data object.
/// Responsible for storing API error status and details.\n
/// Specific errors are derived from this class.
///
/// @note Data members are made public for direct access
///
/// General usage pattern:
/// - call Api::get to obtain response for a FRED data request
/// - on successful request, the response is good and its error is not set
/// - otherwise, response is not good, and error status, code and message are set
///
/// @see ApiResponse

struct ApiError {

  /// API request execution status.
  typedef enum {
    FREDCPP_SUCCESS = 0,
    FREDCPP_ERROR,
    FREDCPP_INTERNAL_ERROR,
    FREDCPP_FAIL_HTTP,
    FREDCPP_FAIL_PARSE,
  } ApiStatus;

  std::string code;
  std::string message;
  ApiStatus status;


  virtual ~ApiError();

  /// Predicate to support !error test.
  /// true when status is success.
  virtual bool operator! () const;

  virtual std::ostream& print(std::ostream& os) const;
  virtual void clear();
};

std::ostream& operator<< (std::ostream& os, const ApiError& object);

//______________________________________________________________________________

class ApiRequest; // forward

namespace internal {
class HttpRequest; // forward
class HttpResponse; // forward
} // namespace internal


/// Data object to describe error at execution of HTTP request to FRED API.
struct ErrorHttpRequestFailed : public ApiError {
  ErrorHttpRequestFailed(const ApiRequest& request, const internal::HttpRequest& httpRequest, const internal::HttpResponse& httpResponse);
};


/// Data object to describe error at parsing of response content received from FRED API.
struct ErrorXmlParseFailed : public ApiError {
  ErrorXmlParseFailed(const ApiRequest& request, const std::istringstream& xmlContent);
};

/// Data object to describe an internal `fredcpp` error.
struct FatalInternalError : public ApiError {
  FatalInternalError(const std::string& reason);
};


} // namespace fredcpp

#endif // FREDCPP_APIERROR_H_