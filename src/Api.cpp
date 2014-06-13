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

#include <config.h>

#include <fredcpp/Api.h>
#include <fredcpp/ApiRequest.h>
#include <fredcpp/ApiResponse.h>
#include <fredcpp/ApiLog.h>

#include <fredcpp/internal/HttpRequestExecutor.h>
#include <fredcpp/internal/HttpRequest.h>
#include <fredcpp/internal/HttpResponse.h>

#include <fredcpp/internal/XmlResponseParser.h>

#include <iostream>
#include <cstdlib>
#include <string>

#include <cassert>


namespace fredcpp {

const std::string Api::DEFAULT_BASE_URI("http://api.stlouisfed.org/fred");
const std::string Api::FRED_PARAM_API_KEY("api_key");
const std::string Api::FRED_PARAM_FILE_TYPE("file_type");


Api::Api(const std::string& apiURI)
  : apiURI_(apiURI)
  , executor_(NULL)
  , parser_(NULL) {
}


Api::~Api() {
}


Api& Api::withLogger(internal::Logger& logger) {
  ApiLog::configure()
    .withLogger(&logger);
  return (*this);
}


Api& Api::withExecutor(internal::HttpRequestExecutor& executor) {
  executor_ = &executor;
  return (*this);
}


Api& Api::withParser(internal::XmlResponseParser& parser) {
  parser_ = &parser;
  return (*this);
}


Api& Api::withKey(const std::string& key) {
  apiKey_ = key;
  return (*this);
}


Api& Api::withFileType(const std::string& type) {
  apiFileType_ = type;
  return (*this);
}


bool Api::get(const ApiRequest& request, ApiResponse& response) {

  response.clear();

  // validate
  bool requireValidExecutor(executor_ != NULL);
  if (!requireValidExecutor) {
    assert(requireValidExecutor && "Valid HttpRequestExecutor implementation expected.");
    response.setError( FatalInternalError("Api Executor is not set.") );
    return (response.good());
  }

  bool requireValidParser(parser_ != NULL);
  if (!requireValidParser) {
    assert(requireValidParser && "Valid XmlResponseParser implementation expected.");
    response.setError( FatalInternalError("Api Parser is not set.") );
    return (response.good());
  }

  FREDCPP_LOG_DEBUG("request:" << request);


  // prepare request (ApiRequest >> HttpRequest)

  std::string URI(std::string(apiURI_).append("/").append(request.getPath()));

  internal::HttpRequest httpRequest(URI, request);
  httpRequest.with(FRED_PARAM_API_KEY, apiKey_);
  if (!apiFileType_.empty()) {
    httpRequest.with(FRED_PARAM_FILE_TYPE, apiFileType_);
  }

  FREDCPP_LOG_DEBUG("http-request:" << httpRequest);


  // execute request

  internal::HttpResponse httpResponse;

  executor_->execute(httpRequest, httpResponse);

  if (!httpResponse.isXmlContent()) {
    response.setError( ErrorHttpRequestFailed(request, httpRequest, httpResponse) );
    FREDCPP_LOG_ERROR( response.error.message);

    return (response.good());
  }

  // process response

  //std::ofstream os("fred_dbg.bin",std::ifstream::binary);
  //os << httpResponse.getContentStream().str();

  std::istringstream xmlContent(httpResponse.getContentStream().str());

  FREDCPP_LOG_DEBUG("http-response:" << httpResponse.getHttpStatus()
                    << " " << "content-type:" << httpResponse.getContentType());

  FREDCPP_LOG_DBGN(2, "content:{\n" << xmlContent.str() << "\n}");

  if ( !parser_->parse(xmlContent, response) ) {
    response.setError( ErrorXmlParseFailed(request, xmlContent) );
    FREDCPP_LOG_ERROR( response.error.message );

    return (response.good());
  }

  response.setErrorFromResult();

  //TOADD:FREDCPP_LOG_INFO(response.result, timed)

  return ( response.good() );
}


} // namespace fredcpp
