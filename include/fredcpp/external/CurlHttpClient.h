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

#ifndef FREDCPP_EXTERNAL_CURLHTTPCLIENT_H_
#define FREDCPP_EXTERNAL_CURLHTTPCLIENT_H_

/// @file
/// Defines `fredcpp` HTTP Request Executor Facility for `cURL` stack.
///
/// @example example1.cpp


#include <fredcpp/internal/HttpRequestExecutor.h>
#include <fredcpp/internal/HttpResponse.h>

#include <curl/curl.h>

#include <string>


namespace fredcpp {
namespace external {


/// HTTP Request Executor Facility instance for `cURL` stack.
///
class CurlHttpClient : public internal::HttpRequestExecutor {
public:
  /// `cURL` write_data callback type.
  typedef std::size_t (*WriteDataCallback)(void* buf, std::size_t size, std::size_t nmemb, void* userp);

  ~CurlHttpClient();

  static CurlHttpClient& getInstance();

  /// @name Configuration Parameters
  /// @{
  CurlHttpClient& withTimeout(unsigned secs);
  CurlHttpClient& withRetryWait(unsigned secs);
  CurlHttpClient& withRetryCount(unsigned count);
  CurlHttpClient& withCACertFile(const std::string& path);
  /// @}


  /// Executes the specified HTTP request and fills HTTP response with resulting content.
  /// Supports re-try in case the request failed due to network issues.\n
  /// Will time-out in case the server has not reponded within specified time.
  ///
  bool execute(const internal::HttpRequest& request, internal::HttpResponse& response);

  std::string encodeURI(const std::string& URI);

  /// @{
  /** Get `cURL` status.
  */
  CURLcode getStatus() const;
  std::string getErrorMsg() const;
  /// @}

  const std::string& getCACertFile() const;


private:
  CurlHttpClient();
  CurlHttpClient(const CurlHttpClient&);
  CurlHttpClient& operator= (const CurlHttpClient&);

  static internal::HttpResponse::HttpStatus httpStatusFromCode(long code);
  static std::size_t writeData(void* buf, std::size_t size, std::size_t nmemb, void* userp);

  static const unsigned DEFAULT_TIMEOUT_SECS;
  static const unsigned DEFAULT_RETRY_WAIT_SECS;
  static const unsigned DEFAULT_RETRY_MAX_COUNT;

  static const std::string DEFAULT_CA_CERT_FILE;
  static const std::string ENV_CA_CERT_FILE;

  long timeoutSecs_;
  unsigned retryWaitSecs_;
  unsigned retryMaxCount_;
  std::string CACertFile_;

  WriteDataCallback writeDataCallback_;
  CURLcode CURLStatus_;
  char errorBuf_[CURL_ERROR_SIZE];
};

} // namespace external
} // namespace fredcpp

#endif // FREDCPP_EXTERNAL_CURLHTTPCLIENT_H_
