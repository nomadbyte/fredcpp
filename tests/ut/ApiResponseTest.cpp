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

#include <fredcpp-gtest.h>
#include <gtest/gtest.h>

#include <fredcpp/ApiResponse.h>


static void mockApiResponseError400(fredcpp::ApiResponse& response) {
  response.clear();

  response.result.name = "error";
  response.result.attributes["code"] = "400";
  response.result.attributes["message"] = "Bad Request.  The value for variable api_key is not a 32 character alpha-numeric lower-case string.  Read http://api.stlouisfed.org/api_key.html for more information.";
}


TEST(ApiResponse, ReceivesApiError) {
  FREDCPP_TESTCASE("Receives error code and message from API");
  using namespace fredcpp;

  ApiResponse response;

  mockApiResponseError400(response);

  ASSERT_TRUE(!response.good());

  response.setErrorFromResult();
  ASSERT_EQ("400", response.error.code);
}
