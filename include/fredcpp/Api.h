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

#ifndef FREDCPP_API_H_
#define FREDCPP_API_H_

/// @file
/// Defines fredcpp::Api class, the principal class to interact with FRED API.

/// @example example1.cpp
/// @example example2.cpp
/// @example example3.cpp


#include <string>


namespace fredcpp {
namespace internal {

class HttpRequestExecutor; // forward
class XmlResponseParser; // forward
class Logger; // forward

} // namespace internal

class ApiRequest; // forward
struct ApiResponse; // forward


/// Interface to FRED database API.
/// Responsible for retrieving FRED data by forwarding queries to FRED API.
/// Coordinates HTTP request creation, execution, and response processing.
///
/// General usage pattern:
/// - configure Logger, Executor, and Parser Facilities (with implementations of
///   internal::Logger, internal::HttpRequestExecutor, internal::XmlResponseParser
///   interfaces)
/// - configure with FRED API key
/// - call Api::get function for the specific ApiRequest object created with
///   ApiRequestBuilder or explicitly
/// - on success, the passed ApiResponse object contains the requested FRED data
/// - otherwise, error is set in the resulting ApiResponse object

class Api {
public:

  /// Construct a default FRED API object with specified base URI
  explicit Api(const std::string& apiURI = DEFAULT_BASE_URI);
  virtual ~Api();

  /// @name Configuration Parameters
  /// Set internal facilities, API key and common parameters.
  /// @{
  Api& withLogger(internal::Logger& logger);
  Api& withExecutor(internal::HttpRequestExecutor& executor);
  Api& withParser(internal::XmlResponseParser& parser);

  Api& withKey(const std::string& key);
  Api& withFileType(const std::string& type);
  /// @}


  /// Execute the specified API request and fill the resulting response.
  virtual bool get(const ApiRequest& request, ApiResponse& response);


private:
  static const std::string DEFAULT_BASE_URI;
  static const std::string FRED_PARAM_API_KEY;
  static const std::string FRED_PARAM_FILE_TYPE;

  const std::string apiURI_;

  std::string apiKey_;
  std::string apiFileType_;
  internal::HttpRequestExecutor* executor_;
  internal::XmlResponseParser* parser_;
};

} //namespace fredcpp

#endif // FREDCPP_API_H_
