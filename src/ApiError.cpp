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

#include <fredcpp/ApiError.h>

#include <fredcpp/ApiRequest.h>
#include <fredcpp/internal/HttpRequest.h>
#include <fredcpp/internal/HttpResponse.h>


namespace fredcpp {

ApiError::ApiError() {
  clear();
}


ApiError::~ApiError() {
}

bool ApiError::operator! () const {
  return (FREDCPP_SUCCESS == status);
}

std::ostream& ApiError::print(std::ostream& os) const {
  os << code << ":" << message
     << " status:" << status
     ;

  return (os);
}

std::ostream& operator<< (std::ostream& os, const ApiError& object) {
  return (object.print(os));
}

void ApiError::clear() {
  code.clear();
  message.clear();

  code = "";
  message = "";
  status = FREDCPP_INTERNAL_ERROR;
}

//______________________________________________________________________________

ErrorHttpRequestFailed::ErrorHttpRequestFailed(const ApiRequest& request, const internal::HttpRequest& httpRequest, const internal::HttpResponse& httpResponse) {
  status = FREDCPP_FAIL_HTTP;

  std::ostringstream buf;
  buf << "Bad Response."
      << " "
      << " Could not connect to API URI or received unexpected content type."
      << " http-status:" << httpResponse.getHttpStatus()
      << " content-type:" << httpResponse.getContentType()
      << " http-request:" << httpRequest
      ;

  message = buf.str();

  buf.str("");
  buf << httpResponse.getHttpStatus();
  code = buf.str();
}

ErrorXmlParseFailed::ErrorXmlParseFailed(const ApiRequest& request, const std::istringstream& xmlContent) {
  status = FREDCPP_FAIL_PARSE;

  std::ostringstream buf;
  buf << "Bad Response."
      << " "
      << " XML response from API is invalid or has unexpected XML schema."
      << " request:" << request
      << " content-begin:{\n" << xmlContent.str() << "\n}:content-end"
      ;

  message = buf.str();
}

FatalInternalError::FatalInternalError(const std::string& reason) {
  status = FREDCPP_INTERNAL_ERROR;

  std::ostringstream buf;
  buf << "fredcpp Internal Error."
      << " "
      << " " << reason
      ;

  message = buf.str();
}

} // namespace fredcpp
