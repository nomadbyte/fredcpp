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

#include <fredcpp-testutils.h>

#include <fredcpp-gtest.h>
#include <gtest/gtest.h>

#include <fredcpp/Api.h>

#include <fredcpp/ApiLog.h>
#include <fredcpp/ApiRequestBuilder.h>
#include <fredcpp/ApiResponse.h>

#include <MockHttpClient.h>
#include <MockXmlParser.h>
#include <MockLogger.h>



TEST(Api, RequiresValidHttpClient) {
  FREDCPP_TESTCASE("Requires a reference to a valid HttpRequestExecutor implementation");
  using namespace fredcpp;

  Api api;

  api.withParser(MockXmlParser::getInstance())
     .withLogger(MockLogger::getInstance());

  ApiResponse response;
  bool result(false);

  //result = api.get(ApiRequestBuilder::Series("TEST-ID"), response); //FAILS-ASSERT:uncomment to test
  ASSERT_FALSE(result);

  api.withExecutor(MockHttpClient::getInstance());

  result = api.get(ApiRequestBuilder::Series("TEST-ID"), response);
  ASSERT_TRUE(result);
}


TEST(Api, RequiresValidXmlParser) {
  FREDCPP_TESTCASE("Requires a reference to a valid XmlResponseParser implementation");
  using namespace fredcpp;

  Api api;

  api.withExecutor(MockHttpClient::getInstance())
     .withLogger(MockLogger::getInstance());

  ApiResponse response;
  bool result(false);

  //result = api.get(ApiRequestBuilder::Series("TEST-ID"), response); //FAILS-ASSERT:uncomment to test
  ASSERT_FALSE(result);

  api.withParser(MockXmlParser::getInstance());
  result = api.get(ApiRequestBuilder::Series("TEST-ID"), response);
  ASSERT_TRUE(result);
}


TEST(Api, RequiresValidLogger) {
  FREDCPP_TESTCASE("Requires a reference to a valid Logger implementation");
  using namespace fredcpp;

  // Reset ApiLog's config to default in case it was already configured
  ApiLog::configure();

  Api api;

  api.withParser(MockXmlParser::getInstance())
     .withExecutor(MockHttpClient::getInstance());

  ApiResponse response;
  bool result(false);

  //result = api.get(ApiRequestBuilder::Series("TEST-ID"), response); //FAILS-ASSERT:uncomment to test
  ASSERT_FALSE(result);

  api.withLogger(MockLogger::getInstance());
  result = api.get(ApiRequestBuilder::Series("TEST-ID"), response);
  ASSERT_TRUE(result);
}


TEST(Api, ReturnsSuccessOnOkRequest) {
  FREDCPP_TESTCASE("Returns success on completed request");
  using namespace fredcpp;

  Api api;

  api.withExecutor(MockHttpClient::getInstance())
     .withParser(MockXmlParser::getInstance())
     .withLogger(MockLogger::getInstance());

  ApiResponse response;
  bool result(false);

  MockHttpClient::getInstance().withExecuteMode(MockHttpClient::MOCK_OK);
  MockXmlParser::getInstance().withParseMode(MockXmlParser::MOCK_OK);

  result = api.get(ApiRequestBuilder::Series("TEST-ID"), response);
  ASSERT_TRUE(result);
  ASSERT_EQ(ApiError::FREDCPP_SUCCESS, response.error.status);
}


TEST(Api, ErrorWhenParserFailed) {
  FREDCPP_TESTCASE("Responds with error when HTTP response parsing failed");
  using namespace fredcpp;

  Api api;

  api.withExecutor(MockHttpClient::getInstance())
     .withParser(MockXmlParser::getInstance())
     .withLogger(MockLogger::getInstance());

  ApiResponse response;
  bool result(false);

  MockXmlParser::getInstance().withParseMode(MockXmlParser::MOCK_FAIL);

  result = api.get(ApiRequestBuilder::Series("TEST-ID"), response);
  ASSERT_FALSE(result);
  ASSERT_EQ(ApiError::FREDCPP_FAIL_PARSE, response.error.status);
}


TEST(Api, ErrorWhenHttpFailed) {
  FREDCPP_TESTCASE("Responds with error when HTTP request failed");
  using namespace fredcpp;

  Api api;

  api.withExecutor(MockHttpClient::getInstance())
     .withParser(MockXmlParser::getInstance())
     .withLogger(MockLogger::getInstance());

  ApiResponse response;
  bool result(false);

  MockHttpClient::getInstance().withExecuteMode(MockHttpClient::MOCK_FAIL);

  result = api.get(ApiRequestBuilder::Series("TEST-ID"), response);
  ASSERT_FALSE(result);
  ASSERT_EQ(ApiError::FREDCPP_FAIL_HTTP, response.error.status);
}


TEST(Api, ErrorResponseWhenApiError) {
  FREDCPP_TESTCASE("Returns error response when received error from API");
  using namespace fredcpp;

  Api api;

  api.withExecutor(MockHttpClient::getInstance())
     .withParser(MockXmlParser::getInstance())
     .withLogger(MockLogger::getInstance());

  ApiResponse response;
  bool result(false);

  MockHttpClient::getInstance()
    .withExecuteMode(MockHttpClient::MOCK_ERROR)
    .withDataContent(fredcpp::test::harmonizePath("data/err400_bad_request_api_key.xml"));

  MockXmlParser::getInstance()
    .withParseMode(MockXmlParser::MOCK_ERROR);

  result = api.get(ApiRequestBuilder::Series("TEST-ID"), response);
  ASSERT_FALSE(result);
  ASSERT_EQ(ApiError::FREDCPP_ERROR, response.error.status);
  ASSERT_FALSE(!response.error);

  ASSERT_EQ("400", response.error.code);
  ASSERT_FALSE(response.error.message.empty());
}


