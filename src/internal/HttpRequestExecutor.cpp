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

#include <fredcpp/internal/HttpRequestExecutor.h>
#include <fredcpp/internal/HttpRequest.h>
#include <fredcpp/internal/HttpResponse.h>

#include <fredcpp/version.h>

#include <sstream>

#include <cassert>


namespace fredcpp {
namespace internal {

const char HttpRequestExecutor::QUERY_SEPARATOR_CHAR('?');
const char HttpRequestExecutor::QUERY_PARAM_SEPARATOR_CHAR('&');
const char HttpRequestExecutor::QUERY_PARAM_ASSIGNMENT_CHAR('=');
const std::string HttpRequestExecutor::DEFAULT_USER_AGENT_NAME(FREDCPP_BRIEF);


HttpRequestExecutor::HttpRequestExecutor(const std::string& userAgent)
  : userAgent_(userAgent)
  , querySeparatorChar_(QUERY_SEPARATOR_CHAR)
  , queryParamSeparatorChar_(QUERY_PARAM_SEPARATOR_CHAR)
  , queryParamAssignmentChar_(QUERY_PARAM_ASSIGNMENT_CHAR)
 {
}


HttpRequestExecutor::~HttpRequestExecutor() {
}


HttpRequestExecutor& HttpRequestExecutor::withUserAgent(const std::string& userAgent) {
  userAgent_ = userAgent;
  return (*this);
}


std::string HttpRequestExecutor::getRequestString(const HttpRequest& request) {
  std::ostringstream buf;

  buf << request.getURI();


  /// @attention Only GET method is currently supported

  bool requireValidHttpMethod( HttpRequest::HTTP_GET == request.getMethod() );

  assert( requireValidHttpMethod &&  "Only HTTP GET method supported");

  if (!requireValidHttpMethod) {
    return (buf.str());
  }


  // Append encoded query parameters

  const KeyValueMap& params(request.getParams());

  int i = 0;
  for (KeyValueMap::const_iterator it = params.begin();
       it != params.end();
       ++it) {

    buf << ( i++ ? queryParamSeparatorChar_ : querySeparatorChar_)
        << encodeURI(it->first)
        << queryParamAssignmentChar_ << encodeURI(it->second);
  }

  return (buf.str());
}


} // namespace internal
} // namespace fredcpp
