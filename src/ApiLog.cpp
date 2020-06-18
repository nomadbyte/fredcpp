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

#include <fredcpp/ApiLog.h>

#include <cassert>


namespace fredcpp {


ApiLog& ApiLog::getInstance() {
  static ApiLog instance;
  return (instance);
}

ApiLog& ApiLog::configure() {
  ApiLog& instance = getInstance();
  instance.initialize();
  return (instance);
}


ApiLog& ApiLog::withLogger(internal::Logger* loggerPtr) {

  if (!requireValidLogger(loggerPtr)) {
    assert(requireValidLogger(loggerPtr) && "Valid logger expected");
    return (*this);
  }

  loggerPtr_ = loggerPtr;

  return (*this);
}


ApiLog& ApiLog::withDebugDepth(int depth) {

  if (!requireValidLogger(loggerPtr_)) {
    assert(requireValidLogger(loggerPtr_) && "Valid logger expected");
    return (*this);
  }

  debugDepth_ = depth;

  return (*this);
}

void ApiLog::info(const std::string& message, const internal::LogContext& context) {

  if (!requireValidLogger(loggerPtr_)) {
    assert(requireValidLogger(loggerPtr_) && "Valid logger expected");
    return;
  }

  loggerPtr_->logMessage(internal::LogLevel::LOG_INFO, message, context);
}

void ApiLog::warn(const std::string& message, const internal::LogContext& context) {

  if (!requireValidLogger(loggerPtr_)) {
    assert(requireValidLogger(loggerPtr_) && "Valid logger expected");
    return;
  }

  loggerPtr_->logMessage(internal::LogLevel::LOG_WARN, message, context);
}

void ApiLog::error(const std::string& message, const internal::LogContext& context) {

  if (!requireValidLogger(loggerPtr_)) {
    assert(requireValidLogger(loggerPtr_) && "Valid logger expected");
    return;
  }

  loggerPtr_->logMessage(internal::LogLevel::LOG_ERROR, message, context);
}

void ApiLog::fatal(const std::string& message, const internal::LogContext& context) {

  if (!requireValidLogger(loggerPtr_)) {
    assert(requireValidLogger(loggerPtr_) && "Valid logger expected");
    return;
  }

  loggerPtr_->logMessage(internal::LogLevel::LOG_FATAL, message, context);
}

void ApiLog::debug(const std::string& message, const internal::LogContext& context) {
  debug(0, message, context);
}

void ApiLog::debug(int depth, const std::string& message, const internal::LogContext& context) {

  if (depth > debugDepth_) {
    return;
  }

  if (!requireValidLogger(loggerPtr_)) {
    assert(requireValidLogger(loggerPtr_) && "Valid logger expected");
    return;
  }

  loggerPtr_->logMessage(internal::LogLevel::LOG_DEBUG, message, context);
}

bool ApiLog::infoEnabled() const {
  bool result(false);

  if (!requireValidLogger(loggerPtr_)) {
    assert(requireValidLogger(loggerPtr_) && "Valid logger expected");
    return (result);
  }

  result = loggerPtr_->levelEnabled(internal::LogLevel::LOG_INFO);
  return (result);
}

bool ApiLog::warnEnabled() const {
  bool result(false);

  if (!requireValidLogger(loggerPtr_)) {
    assert(requireValidLogger(loggerPtr_) && "Valid logger expected");
    return (result);
  }

  result = loggerPtr_->levelEnabled(internal::LogLevel::LOG_WARN);
  return (result);
}

bool ApiLog::errorEnabled() const {
  bool result(false);

  if (!requireValidLogger(loggerPtr_)) {
    assert(requireValidLogger(loggerPtr_) && "Valid logger expected");
    return (result);
  }

  result = loggerPtr_->levelEnabled(internal::LogLevel::LOG_ERROR);
  return (result);
}

bool ApiLog::fatalEnabled() const {
  bool result(false);

  if (!requireValidLogger(loggerPtr_)) {
    assert(requireValidLogger(loggerPtr_) && "Valid logger expected");
    return (result);
  }

  result = loggerPtr_->levelEnabled(internal::LogLevel::LOG_FATAL);
  return (result);
}

bool ApiLog::debugEnabled() const {
  bool result(false);

  if (!requireValidLogger(loggerPtr_)) {
    assert(requireValidLogger(loggerPtr_) && "Valid logger expected");
    return (result);
  }

  result = loggerPtr_->levelEnabled(internal::LogLevel::LOG_DEBUG);
  return (result);
}

ApiLog::ApiLog() {
  initialize();
}

void ApiLog::initialize() {
  loggerPtr_ = NULL;
  debugDepth_ = 0;
}

bool ApiLog::requireValidLogger(internal::Logger* const loggerPtr) const {
  return (NULL != loggerPtr);
}


} // namespace fredcpp
