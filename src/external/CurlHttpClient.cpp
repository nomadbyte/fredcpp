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

#include <fredcpp/external/CurlHttpClient.h>

#include <fredcpp/ApiLog.h>

#include <fredcpp/internal/HttpRequest.h>
#include <fredcpp/internal/HttpResponse.h>
#include <fredcpp/internal/utils.h>

#include <iostream>


namespace fredcpp {
namespace external {

const unsigned CurlHttpClient::DEFAULT_TIMEOUT_SECS(15);
const unsigned CurlHttpClient::DEFAULT_RETRY_WAIT_SECS(5);
const unsigned CurlHttpClient::DEFAULT_RETRY_MAX_COUNT(3);


CurlHttpClient::CurlHttpClient()
  : internal::HttpRequestExecutor("libcurl-agent/1.0")
  , timeoutSecs_(DEFAULT_TIMEOUT_SECS)
  , retryWaitSecs_(DEFAULT_RETRY_WAIT_SECS)
  , retryMaxCount_(DEFAULT_RETRY_MAX_COUNT)
  , CURLStatus_(CURLE_FAILED_INIT)
  , writeDataCallback_(writeData) {

	curl_global_init(CURL_GLOBAL_ALL);
  errorBuf_[0] = '\0';
}


CurlHttpClient::~CurlHttpClient() {
	curl_global_cleanup();
}


CurlHttpClient& CurlHttpClient::getInstance() {
  static CurlHttpClient instance;
  return (instance);
}


CurlHttpClient& CurlHttpClient::withTimeout(unsigned secs) {
  timeoutSecs_ = secs;
  return (*this);
}


CurlHttpClient& CurlHttpClient::withRetryWait(unsigned secs) {
  retryWaitSecs_ = secs;
  return (*this);
}


CurlHttpClient& CurlHttpClient::withRetryCount(unsigned count) {
  retryMaxCount_ = count;
  return (*this);
}


bool CurlHttpClient::execute(const internal::HttpRequest& request, internal::HttpResponse& response) {
	CURLStatus_ = CURLE_FAILED_INIT;
  errorBuf_[0] = '\0';

  bool retry(false);
  unsigned retryCount(0);

  response.clear();

	CURL* curl = curl_easy_init();

  if (NULL == curl) {
    return (internal::HttpResponse::HTTP_OK == response.getHttpStatus());
  }

  std::string URI(getRequestString(request));

  FREDCPP_LOG_DEBUG("CURL:URI:" << URI);

  if (CURLE_OK == (CURLStatus_ = curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent_.c_str()))
      && CURLE_OK == (CURLStatus_ = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeDataCallback_))
      && CURLE_OK == (CURLStatus_ = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
      && CURLE_OK == (CURLStatus_ = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
      && CURLE_OK == (CURLStatus_ = curl_easy_setopt(curl, CURLOPT_FILE, &response.getContentStream()))
      && CURLE_OK == (CURLStatus_ = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeoutSecs_))
      && CURLE_OK == (CURLStatus_ = curl_easy_setopt(curl, CURLOPT_URL, URI.c_str()))
      && CURLE_OK == (CURLStatus_ = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuf_))
      ) {

    do {
      CURLStatus_ = curl_easy_perform(curl);

      if (CURLE_OK == CURLStatus_) {
        // on successfull call get http-status and content-type

        long code(0L);
        char *strInfo(NULL);
        if (CURLE_OK == curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code)
            && CURLE_OK == curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &strInfo)) {
          response.setHttpStatus(httpStatusFromCode(code));
          response.setContentType(strInfo);
        }

      } else {
        FREDCPP_LOG_DEBUG("CURL:Request failed CURLStatus:" << CURLStatus_
                          << "|" << errorBuf_);
      }

      retry = (CURLE_OPERATION_TIMEDOUT == CURLStatus_
               || CURLE_COULDNT_RESOLVE_HOST == CURLStatus_
               || CURLE_COULDNT_RESOLVE_PROXY == CURLStatus_
               || CURLE_COULDNT_CONNECT == CURLStatus_);

      if (retry) {
        if (retryCount < retryMaxCount_) {
          ++retryCount;
          FREDCPP_LOG_DEBUG("CURL:Waiting " << retryWaitSecs_ << "ms"
                            << " before request retry " << retryCount << " ...");
          internal::sleep(retryWaitSecs_);

        } else {
          retry = false;
          FREDCPP_LOG_DEBUG("CURL:Retry maximum count " << retryMaxCount_ << " reached - giving up.");
        }
      }

    } while (retry);
  }

  if (CURLE_OK == CURLStatus_) {
    FREDCPP_LOG_DEBUG("CURL:http-response:" << response.getHttpStatus()
                      << " " << "content-type:" << response.getContentType());

  }

  curl_easy_cleanup(curl);

  return (internal::HttpResponse::HTTP_OK == response.getHttpStatus());
}


std::string CurlHttpClient::encodeURI(const std::string& URI) {
  std::string result;

	CURL* curl = curl_easy_init();

  char* buf = curl_easy_escape(curl, URI.c_str(), URI.size());
  if (NULL == buf ) {
    //error
    return result;
  }

  result = std::string(buf);
  curl_free(buf);

  curl_easy_cleanup(curl);


  // FIXUP: curl appears to also encode '_' (%5F), so need to undo this

  struct URIEncodeDef {
    std::string raw, encoded;
  };
  const URIEncodeDef UNDERSCORE = {"_","%5F"};

  const std::string& search = UNDERSCORE.encoded;
  const std::string& replaceWith = UNDERSCORE.raw;

  size_t pos = 0;

  while ((pos = result.find(search, pos)) != std::string::npos) {
    result.replace(pos, search.length(), replaceWith);
    pos += replaceWith.length();
  }

  return (result);
}


CURLcode CurlHttpClient::getStatus() const {
  return (CURLStatus_);
}


std::string CurlHttpClient::getErrorMsg() const {
  return (std::string(errorBuf_));
}


internal::HttpResponse::HttpStatus CurlHttpClient::httpStatusFromCode(long code) {
  internal::HttpResponse::HttpStatus status(internal::HttpResponse::HTTP_UNKNOWN);

  // valid code: [HTTP_CONTINUE:101, HTTP_VERSION_NOT_SUPPORTED:505]
  if (code >= internal::HttpResponse::HTTP_CONTINUE
      && code <= internal::HttpResponse::HTTP_VERSION_NOT_SUPPORTED) {
    status = static_cast<internal::HttpResponse::HttpStatus>(code);
  }

  return (status);
}


// callback function writes data to a std::ostream
size_t CurlHttpClient::writeData(void* buf, size_t size, size_t nmemb, void* userp)
{
	if (userp == NULL) {
    // error
    return 0;
	}

  std::ostream& os = *static_cast<std::ostream*>(userp);
  std::streamsize len = size * nmemb;

  if (!(os.write(static_cast<char*>(buf), len)) ) {
    // error
    return 0;
  }

  return (len);
}


} // namespace external
} // namespace fredcpp

