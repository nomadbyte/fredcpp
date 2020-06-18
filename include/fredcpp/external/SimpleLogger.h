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

#ifndef FREDCPP_EXTERNAL_SIMPLELOGGER_H_
#define FREDCPP_EXTERNAL_SIMPLELOGGER_H_

/// @file
/// Simple logging framework.
///
/// @example example1.cpp


#include <fredcpp/internal/Logger.h>


namespace fredcpp {
namespace external {


/// Logging output stream of specified priority level.

class LogChannel {
public:
  LogChannel(internal::LogLevel::Level level = internal::LogLevel::LOG_NULL, std::ostream& os = std::cout);

  void writeLine(const std::string& str);

  bool enable();
  bool disable();
  void setOutput(std::ostream& os);
  void setLevel(internal::LogLevel::Level level);

  internal::LogLevel::Level getLevel() const;
  bool enabled() const;

private:
  LogChannel(const LogChannel&);
  LogChannel& operator= (const LogChannel&);

  bool isNull() const;

  std::ostream* osPtr_;
  internal::LogLevel::Level level_;
  bool enabled_;
};

//______________________________________________________________________________

/// Log-file output stream to be bound to LogChannel.

class LogFile {
public:
  LogFile();
  LogFile(const std::string& path);
  ~LogFile();

  bool openNew(const std::string& path);
  bool openForAppend(const std::string& path);
  void close();

  std::ofstream& useStream();

  const std::string& getPath() const;
  bool isOpen() const;

private:
  bool open(std::ios_base::openmode mode);

  std::string path_;
  std::ofstream ofs_;
};

//______________________________________________________________________________

/// Simple logging framework with `fredcpp` binding.
///
/// Features:
/// - multiple logging priority levels
/// - output to standard or file streams
/// - implements fredcpp::internal::Logger interface

class SimpleLogger : public internal::Logger {
public:
  typedef std::ostream& (*LogFormatter)(std::ostream& os, internal::LogLevel::Level level, const std::string& message, const internal::LogContext& context);

  ~SimpleLogger();

  static SimpleLogger& getInstance();

  void logMessage(internal::LogLevel::Level level, const std::string& message, const internal::LogContext& context);

  /// @name Configuration
  /// @{
  void setOutput(internal::LogLevel::Level level, std::ostream& os);
  void setOutput(internal::LogLevel::Level level, const std::string& path);
  void setOutput(std::ostream& os);
  void setOutput(const std::string& path);
  void setFormatter(LogFormatter formatter);
  /// @}


  /// @name Priority Level Toggles
  /// @{
  bool levelEnabled(internal::LogLevel::Level level) const;
  bool enableLevel(internal::LogLevel::Level level);
  bool disableLevel(internal::LogLevel::Level level);

  bool enableInfo();
  bool enableWarn();
  bool enableError();
  bool enableFatal();
  bool enableDebug();

  bool disableInfo();
  bool disableWarn();
  bool disableError();
  bool disableFatal();
  bool disableDebug();
  /// @}


private:
  SimpleLogger();

  SimpleLogger(const SimpleLogger&);
  SimpleLogger& operator= (const SimpleLogger&);

  void setupChannel(internal::LogLevel::Level level);
  LogChannel& useChannel(internal::LogLevel::Level level);
  LogFile& useFile(internal::LogLevel::Level level);
  LogFile* findFile(const std::string& path);

  const LogChannel& getNullChannel() const;
  const LogChannel& getChannel(internal::LogLevel::Level level) const;

  std::ostream& formatMessage(std::ostream& os, internal::LogLevel::Level level, const std::string& message, const internal::LogContext& context);

  bool requireValidLevel(internal::LogLevel::Level level) const;


  LogChannel channels_[internal::LogLevel::maxLevel];
  LogFile files_[internal::LogLevel::maxLevel];
  LogFormatter formatter_;
};

/// Default Log Formatter.
std::ostream& defaultLogFormat(std::ostream& os, internal::LogLevel::Level level, const std::string& message, const internal::LogContext& context);

} // namespace external
} // namespace fredcpp

#endif // FREDCPP_EXTERNAL_SIMPLELOGGER_H_
