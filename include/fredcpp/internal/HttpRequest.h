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

#ifndef FREDCPP_INTERNAL_HTTPREQUEST_H_
#define FREDCPP_INTERNAL_HTTPREQUEST_H_


/// @file
/// Defines HTTP request.


#include <fredcpp/internal/Request.h>

#include <ostream>
#include <string>


namespace fredcpp {
namespace internal {


/// HTTP request.
/// Manages HTTP request URI and query parameters.
///
/// @attention Currently only GET method is supported.

class HttpRequest : public Request {
public:
  typedef enum {
    HTTP_GET = 0,
    maxMethod
  } Method;

  explicit HttpRequest(const std::string& URI = "");
  explicit HttpRequest(const std::string& URI, const Request& request);
  virtual ~HttpRequest();

  /// @name Configuration
  /// @{
  HttpRequest& withURI(const std::string& URI);
  HttpRequest& withParams(const Request& request);
  /// @}

  const std::string& getURI() const;
  Method getMethod() const;

  virtual std::ostream& print(std::ostream& os) const;

private:
  static const char* HTTP_METHODS[maxMethod];

  Method method_;
  std::string URI_;
};


std::ostream& operator<< (std::ostream& os, const HttpRequest& object);

} // namespace internal
} // namespace fredcpp



#endif // FREDCPP_INTERNAL_HTTPREQUEST_H_
