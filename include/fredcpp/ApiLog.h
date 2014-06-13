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

#ifndef FREDCPP_APILOG_H_
#define FREDCPP_APILOG_H_

/// @file
/// Defines fredcpp::ApiLog, `fredcpp` Logging Facility.
///
/// @example example1.cpp


#include <fredcpp/internal/Logger.h>

#include <string>


namespace fredcpp {

/// `fredcpp` Logging Facility.
/// Forwards log messages to a supplied logger which implements Logger interface.
/// Supports progressively inclusive debug message depth - prints all debug messages
/// with depth <= configured depth.
/// Usually called via the defined @ref FREDCPP_LOG "FREDCPP_LOG-macros".

class ApiLog {
public:
  static ApiLog& getInstance();

  static ApiLog& configure();

  /// @name Configuration Parameters
  /// @{
  ApiLog& withLogger(internal::Logger* loggerPtr);
  ApiLog& withDebugDepth(int depth);
  /// @}


  /// @name Logging Functions
  /// Send log message with supplied context details.
  /// @{
  void info(const std::string& message, const internal::LogContext& context);
  void warn(const std::string& message, const internal::LogContext& context);
  void error(const std::string& message, const internal::LogContext& context);
  void fatal(const std::string& message, const internal::LogContext& context);
  void debug(const std::string& message, const internal::LogContext& context);
  void debug(int depth, const std::string& message, const internal::LogContext& context);
  /// @}


  /// @name Logging Predicates
  /// Test if logging level is enabled.
  /// @{
  bool infoEnabled() const;
  bool warnEnabled() const;
  bool errorEnabled() const;
  bool fatalEnabled() const;
  bool debugEnabled() const;
  /// @}


private:
  ApiLog();
  ApiLog(const ApiLog&);
  ApiLog& operator= (const ApiLog&);

  void initialize();

  bool requireValidLogger(internal::Logger* const loggerPtr) const;


  internal::Logger* loggerPtr_;
  int debugDepth_;
};


} // namespace fredcpp

//______________________________________________________________________________


/// @anchor FREDCPP_LOG
///
/// @name Logging Helper Macros
/// Helper macros to simiplify logging in `fredcpp` context.
/// Message stream syntax is supported.
/// @code{.cpp}
///   FREDCPP_LOG_INFO("This is INFO message:" << 123 << "...");
/// @endcode
///
/// @attention Requires fredcpp::ApiLog instance configured with valid
/// fredcpp::internal::Logger implementation.
///
/// @see fredcpp::Api
/// @{
#define FREDCPP_LOGCONTEXT fredcpp::internal::LogContext(__FILE__,__LINE__, FREDCPP__FUNC__) // FREDCPP__PRETTY_FUNC__

#define  FREDCPP_LOG_INFO(message) {\
  fredcpp::ApiLog& log_ = fredcpp::ApiLog::getInstance();\
  if (log_.infoEnabled()) {\
    std::ostringstream buf_;\
    buf_ << message;\
    log_.info(buf_.str(), FREDCPP_LOGCONTEXT); }}

#define  FREDCPP_LOG_WARN(message) {\
  fredcpp::ApiLog& log_ = fredcpp::ApiLog::getInstance();\
  if (log_.warnEnabled()) {\
    std::ostringstream buf_;\
    buf_ << message;\
    log_.warn(buf_.str(), FREDCPP_LOGCONTEXT); }}

#define  FREDCPP_LOG_ERROR(message) {\
  fredcpp::ApiLog& log_ = fredcpp::ApiLog::getInstance();\
  if (log_.errorEnabled()) {\
    std::ostringstream buf_;\
    buf_ << message;\
    log_.error(buf_.str(), FREDCPP_LOGCONTEXT); }}

#define  FREDCPP_LOG_FATAL(message) {\
  fredcpp::ApiLog& log_ = fredcpp::ApiLog::getInstance();\
  if (log_.fatalEnabled()) {\
    std::ostringstream buf_;\
    buf_ << message;\
    log_.fatal(buf_.str(), FREDCPP_LOGCONTEXT); }}

#define  FREDCPP_LOG_DBGN(depth, message) {\
  fredcpp::ApiLog& log_ = fredcpp::ApiLog::getInstance();\
  if (log_.debugEnabled()) {\
    std::ostringstream buf_;\
    buf_ << message;\
    log_.debug((depth), buf_.str(), FREDCPP_LOGCONTEXT); }}

#define  FREDCPP_LOG_DEBUG(message) FREDCPP_LOG_DBGN(0, message)
/// @}

#endif // FREDCPP_APILOG_H_