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

#include <fredcpp/internal/Request.h>


TEST(internalRequest, StoresParamValue) {
  FREDCPP_TESTCASE("Stores a value for a given parameter");
  using namespace fredcpp::internal;

  Request request;
  request.with("key", "value");

  ASSERT_TRUE(request.hasParam("key"));
  ASSERT_EQ("value", request["key"]);
}

TEST(internalRequest, SupportsCaseInsensitiveKeys) {
  FREDCPP_TESTCASE("Supports case-insensitive keys");
  using namespace fredcpp::internal;

  Request request;
  request.with("AnyCaseKey", "value");
  ASSERT_EQ(request["anyCaseKEY"], request["AnyCaseKey"]);

  request.with("ANYCaseKey", "new-value");
  ASSERT_EQ("new-value", request["AnyCaseKey"]);
}


TEST(internalRequest, StoresUniqueParamKeys) {
  FREDCPP_TESTCASE("Duplicate parameter overwrites the stored value");
  using namespace fredcpp::internal;

  Request request;
  request.with("key", "value");
  ASSERT_EQ("value", request["key"]);

  request.with("key", "new-value");
  ASSERT_EQ("new-value", request["key"]);
}

TEST(internalRequest, ErasesStoredParam) {
  FREDCPP_TESTCASE("Erases a stored parameter");
  using namespace fredcpp::internal;

  Request request;
  request.with("key", "value");

  request.eraseParam("key");

  ASSERT_FALSE(request.hasParam("key"));
}

TEST(internalRequest, HandlesEraseOfNonExistingParam) {
  FREDCPP_TESTCASE("Handles erasing of non-existing parameter");
  using namespace fredcpp::internal;

  Request request;
  request.with("key", "value");

  ASSERT_FALSE(request.hasParam("non-existing-param"));
  request.eraseParam("non-existing-param");

  ASSERT_TRUE(request.hasParam("key"));
}

TEST(internalRequest, SupportsEraseAllParams) {
  FREDCPP_TESTCASE("Supports erase all stored parameters");
  using namespace fredcpp::internal;

  Request request;
  request.with("key", "value")
         .with("key2", "value");

  request.clear();

  ASSERT_TRUE(request.getParams().empty());
}
