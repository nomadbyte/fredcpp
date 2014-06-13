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

#ifndef FREDCPP_MOCKHTTPCLIENT_H_
#define FREDCPP_MOCKHTTPCLIENT_H_

#include <fredcpp/internal/HttpRequestExecutor.h>
#include <fredcpp/internal/HttpResponse.h>

#include <string>


namespace fredcpp {

class MockHttpClient : public internal::HttpRequestExecutor {
public:
  typedef enum {
    MOCK_OK = 0,
    MOCK_ERROR,
    MOCK_OK_CONTENT_FILE,
    MOCK_FAIL,
    MOCK_BAD_URI,
    MOCK_BAD_REQUEST,
    MOCK_BAD_CONTENT_TYPE,
  } ExecuteMode;

  static MockHttpClient& getInstance() {
    static MockHttpClient instance;
    return (instance);
  }

  virtual bool execute(const internal::HttpRequest& request, internal::HttpResponse& response);
  virtual std::string encodeURI(const std::string& URI);

  MockHttpClient& withExecuteMode(ExecuteMode mode) {
    executeMode_ = mode;
    return (*this);
  }

  MockHttpClient& withDataContent(const std::string& path) {
    dataFile_ = path;
    return (*this);
  }

  MockHttpClient& withContentType(const std::string& type) {
    contentType_ = type;
    return (*this);
  }

private:
  MockHttpClient()
    : executeMode_(MOCK_OK) {
  }

  bool loadContent(std::ostream& contentStream);

  bool execute_OK(const internal::HttpRequest& request, internal::HttpResponse& response);
  bool execute_ERROR(const internal::HttpRequest& request, internal::HttpResponse& response);
  bool execute_FAIL(const internal::HttpRequest& request, internal::HttpResponse& response);


  ExecuteMode executeMode_;
  std::string dataFile_;
  std::string contentType_;
};


} // namespace fredcpp


//______________________________________________________________________________
// Implementation of HttpRequestExecutor interface

namespace fredcpp {

inline bool MockHttpClient::execute(const internal::HttpRequest& request, internal::HttpResponse& response) {
  bool result(false);

  switch (executeMode_) {
  case MOCK_OK:
    result = execute_OK(request, response);
    break;

  case MOCK_ERROR:
    result = execute_ERROR(request, response);
    break;

  case MOCK_FAIL:
    result = execute_FAIL(request, response);
    break;

  default:
    assert(false && "Unsupported ExecuteMode");
  }

  return (result);
}


inline std::string MockHttpClient::encodeURI(const std::string& URI) {
  std::string result(URI);
  return (result);
}


inline bool MockHttpClient::loadContent(std::ostream& contentStream) {
  bool result(false);

  if (!dataFile_.empty()) {
    std::ifstream ifs(dataFile_.c_str());

    assert(ifs && "Valid content data file expected");

    if (ifs) {
      contentStream << ifs.rdbuf();
      result = true;
    }
  }

  return (result);
}


inline bool MockHttpClient::execute_OK(const internal::HttpRequest& request, internal::HttpResponse& response) {

  response.clear();

  response.setHttpStatus(internal::HttpResponse::HTTP_OK);
  response.setContentType("text/xml; charset=UTF-8");

  loadContent(response.getContentStream());

  return (internal::HttpResponse::HTTP_OK == response.getHttpStatus());
}


inline bool MockHttpClient::execute_ERROR(const internal::HttpRequest& request, internal::HttpResponse& response) {
  response.clear();

  response.setHttpStatus(internal::HttpResponse::HTTP_BAD_REQUEST);
  response.setContentType("text/xml; charset=UTF-8");

  loadContent(response.getContentStream());

  return (internal::HttpResponse::HTTP_OK == response.getHttpStatus());
}


inline bool MockHttpClient::execute_FAIL(const internal::HttpRequest& request, internal::HttpResponse& response) {
  response.clear();

  response.setHttpStatus(internal::HttpResponse::HTTP_BAD_REQUEST);

  return (internal::HttpResponse::HTTP_OK == response.getHttpStatus());
}


} // namespace fredcpp

#endif // FREDCPP_MOCKHTTPCLIENT_H_

