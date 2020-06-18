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

#ifndef FREDCPP_MOCKLOGGER_H_
#define FREDCPP_MOCKLOGGER_H_

#include <fredcpp/internal/Logger.h>

#include <sstream>
#include <string>

#include <cassert>


namespace fredcpp {

class MockLogger: public internal::Logger {
public:
  static MockLogger& getInstance() {
    static MockLogger instance;
    return (instance);
  }

  virtual ~MockLogger() {
  }

  virtual void logMessage(internal::LogLevel::Level level, const std::string& message, const internal::LogContext& context);

  virtual bool enableLevel(internal::LogLevel::Level level);
  virtual bool disableLevel(internal::LogLevel::Level level);
  virtual bool levelEnabled(internal::LogLevel::Level level) const;

  std::string getInfo() const {
    return (info_.buf.str());
  }

  std::string getWarn() const {
    return (warn_.buf.str());
  }

  std::string getError() const {
    return (error_.buf.str());
  }

  std::string getFatal() const {
    return (fatal_.buf.str());
  }

  std::string getDebug() const {
    return (debug_.buf.str());
  }

  void clearLog(internal::LogLevel::Level level) {
    LogSink& log(getLogSink(level));
    log.buf.str("");
  }


private:
  struct LogSink {
    bool enabled;
    int depth;
    internal::LogLevel::Level level;
    std::ostringstream buf;

    LogSink(internal::LogLevel::Level level)
      : enabled(false)
      , depth(0)
      , level(level) {
    }

    void clear() {
      buf.str("");
    }
  };

  MockLogger()
    : info_(internal::LogLevel::LOG_INFO)
    , warn_(internal::LogLevel::LOG_WARN)
    , error_(internal::LogLevel::LOG_ERROR)
    , fatal_(internal::LogLevel::LOG_FATAL)
    , debug_(internal::LogLevel::LOG_DEBUG)
    , null_(internal::LogLevel::LOG_NULL) {
  }

  LogSink& getLogSink(internal::LogLevel::Level level) {
    LogSink *logPtr(NULL);

    switch(level) {
    case internal::LogLevel::LOG_INFO:
      logPtr = &info_;
      break;
    case internal::LogLevel::LOG_WARN:
      logPtr = &warn_;
      break;
    case internal::LogLevel::LOG_ERROR:
      logPtr = &error_;
      break;
    case internal::LogLevel::LOG_FATAL:
      logPtr = &fatal_;
      break;
    case internal::LogLevel::LOG_DEBUG:
      logPtr = &debug_;
      break;
    default:
      assert(false && "Invalid LogLevel");
      logPtr = &null_;
    }

    return (*logPtr);
  }

  LogSink info_;
  LogSink warn_;
  LogSink error_;
  LogSink fatal_;
  LogSink debug_;
  LogSink null_;
};

} // namespace fredcpp

//______________________________________________________________________________

// Implementation of Logger interface

namespace fredcpp {

inline void MockLogger::logMessage(internal::LogLevel::Level level, const std::string& message, const internal::LogContext& context) {
  LogSink& log (getLogSink(level));

  if (log.level != null_.level
      && log.enabled) {
    log.clear();
    log.buf << message;
  }
}

inline bool MockLogger::enableLevel(internal::LogLevel::Level level) {
  LogSink& log(getLogSink(level));
  bool wasEnabled = log.enabled;

  if (log.level != null_.level) {
    log.enabled = true;
  }
  return (wasEnabled);
}

inline bool MockLogger::disableLevel(internal::LogLevel::Level level) {
  LogSink& log(getLogSink(level));
  bool wasEnabled = log.enabled;

  if (log.level != null_.level) {
    log.enabled = false;
  }
  return (wasEnabled);
}

inline bool MockLogger::levelEnabled(internal::LogLevel::Level level) const {
  const LogSink& log(const_cast<MockLogger*>(this)->getLogSink(level));
  return (log.enabled);
}


} // namespace fredcpp


#endif // FREDCPP_MOCKLOGGER_H_
