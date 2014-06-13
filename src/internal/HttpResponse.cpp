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

#include <fredcpp/internal/HttpResponse.h>

namespace fredcpp {
namespace internal {

HttpResponse::HttpResponse()
  : contentType_() {
  clear();
}

HttpResponse::~HttpResponse() {
}

std::ostringstream& HttpResponse::getContentStream() {
  return (content_);
}

void HttpResponse::setContentType(const std::string contentType) {
  contentType_ = contentType;
}

void HttpResponse::setHttpStatus(HttpResponse::HttpStatus status) {
  httpStatus_ = status;
}

const std::string& HttpResponse::getContentType() const {
  return (contentType_);
}

HttpResponse::HttpStatus HttpResponse::getHttpStatus() const {
  return (httpStatus_);
}

bool HttpResponse::isBadRequest() const {
  return (HTTP_BAD_REQUEST == httpStatus_);
}

bool HttpResponse::isXmlContent() const {
  return (std::string::npos != contentType_.find("text/xml"));
}

void HttpResponse::clear() {
  content_.str("");
  contentType_.clear();
  httpStatus_ = HTTP_BAD_REQUEST;
}


} // namespace internal
} // namespace fredcpp
