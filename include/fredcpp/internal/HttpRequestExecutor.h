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

#ifndef FREDCPP_INTERNAL_HTTPREQUESTEXECUTOR_H_
#define FREDCPP_INTERNAL_HTTPREQUESTEXECUTOR_H_

/// @file
/// Defines HTTP Request Executor Facility interface.


#include <string>


namespace fredcpp {
namespace internal {

class HttpRequest; // forward
class HttpResponse; // forward


/// HTTP Request Executor Facility interface.
/// Executes HTTP request and fills the resulting response content.
///
/// Implement this interface for the specific HTTP client stack (e.g. cURL).

class HttpRequestExecutor {
public:
  explicit HttpRequestExecutor(const std::string& userAgent = DEFAULT_USER_AGENT_NAME );
  virtual ~HttpRequestExecutor();

  /// @name Configuration
  /// @{
  HttpRequestExecutor& withUserAgent(const std::string& userUserAgent);
  /// @}


  /// Executes HTTP request and fills the resulting response content.
  /// On successful return, the response's content and status has been set.
    virtual bool execute(const HttpRequest& request, HttpResponse& response) = 0;


  /// Encodes URI string to contain only valid characters.
  /// Converts special characters to HTTP %hex character strings.
  virtual std::string encodeURI(const std::string& URI) = 0;


protected:

  /// Constructs request query string.
  /// Appends encoded query parameters to request's URI.
  virtual std::string getRequestString(const HttpRequest& request);

  char querySeparatorChar_;
  char queryParamSeparatorChar_;
  char queryParamAssignmentChar_;

  std::string userAgent_;


private:
  static const char QUERY_SEPARATOR_CHAR;
  static const char QUERY_PARAM_SEPARATOR_CHAR;
  static const char QUERY_PARAM_ASSIGNMENT_CHAR;
  static const std::string DEFAULT_USER_AGENT_NAME;
};


} // namespace internal
} // namespace fredcpp

#endif // FREDCPP_INTERNAL_HTTPREQUESTEXECUTOR_H_
