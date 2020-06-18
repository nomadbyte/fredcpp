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

#include <fredcpp/internal/HttpRequest.h>
#include <string>
#include <algorithm>


namespace fredcpp {
namespace internal {

const char* HttpRequest::HTTP_METHODS[maxMethod] = {
  "GET",
};

HttpRequest::HttpRequest(const std::string& URI)
  : Request()
  , method_(HttpRequest::HTTP_GET)
  , URI_(URI) {
}

HttpRequest::HttpRequest(const std::string& URI, const Request& request)
  : Request(request)
  , method_(HttpRequest::HTTP_GET)
  , URI_(URI) {
}

HttpRequest::~HttpRequest() {
}

HttpRequest& HttpRequest::withURI(const std::string& URI) {
  URI_ = URI;
  return (*this);
}

HttpRequest& HttpRequest::withParams(const Request& request) {
  setParams(request.getParams());
  return (*this);
}

const std::string& HttpRequest::getURI() const {
  return (URI_);
}

HttpRequest::Method HttpRequest::getMethod() const {
  return (method_);
}

bool HttpRequest::isHttps() const {
    const std::string HTTPS("https:");
    const std::string WHITESPACE(" \t\r\n");
    bool result(false);

    std::size_t pos = URI_.find_first_not_of(WHITESPACE);
    if ( std::string::npos == pos ) {
        // URI empty or whitespace only
        return (result);
    }

    std::string buf = URI_.substr(pos, HTTPS.size());
    std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);

    result = (buf.compare(HTTPS) == 0);

    return (result);
}

std::ostream& HttpRequest::print(std::ostream& os) const {
  // METHOD URI|params

  os << HTTP_METHODS[method_]
     << " " << URI_;

  if (getParams().size()) {
     os << "|";
     Request::print(os);
  }

  return (os);
}


std::ostream& operator<< (std::ostream& os, const HttpRequest& object) {
  return (object.print(os));
}


} // namespace internal
} // namespace fredcpp

