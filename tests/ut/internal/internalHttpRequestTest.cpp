/*
 *  This file is part of fredcpp library
 *
 *  Copyright (c) 2012 - 2015, Artur Shepilko, <fredcpp@nomadbyte.com>.
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

#include <fredcpp-gtest.h>
#include <gtest/gtest.h>

#include <fredcpp/internal/HttpRequest.h>


TEST(internalHttpRequest, StoresURI) {
  FREDCPP_TESTCASE("Stores a URI");
  using namespace fredcpp::internal;

  HttpRequest request;
  request.withURI("http://server.net");

  ASSERT_EQ("http://server.net", request.getURI());
}

TEST(internalHttpRequest, AcceptsQueryParams) {
  FREDCPP_TESTCASE("Stores a URI and query parameters");
  using namespace fredcpp::internal;

  Request params;
  params.with("param1","value1")
        .with("param2","value2")
        ;

  HttpRequest request("http://server.net", params);

  ASSERT_EQ("http://server.net", request.getURI());
  ASSERT_TRUE("value1" == request["param1"]
              && "value2" == request["param2"]);


  params.with("param3","value3");
  request.withParams(params);

  ASSERT_TRUE("value3" == request["param3"]
              && "value1" == request["param1"]
              && "value2" == request["param2"]);

}

TEST(internalHttpRequest, DetectsHttpsURI) {
  FREDCPP_TESTCASE("Detects HTTPS URI");
  using namespace fredcpp::internal;

  HttpRequest request;

  request.withURI("https://server.net");
  ASSERT_TRUE(request.isHttps());

  request.withURI("http://server.net");
  ASSERT_FALSE(request.isHttps());

  request.withURI("");
  ASSERT_FALSE(request.isHttps());

  request.withURI("invalid-uri");
  ASSERT_FALSE(request.isHttps());

  request.withURI("hTtpS:");
  ASSERT_TRUE(request.isHttps());

  request.withURI("  https:");
  ASSERT_TRUE(request.isHttps());

  request.withURI("\t\r\nhttps:");
  ASSERT_TRUE(request.isHttps());
}
