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

#ifndef FREDCPP_INTERNAL_LOGGER_H_
#define FREDCPP_INTERNAL_LOGGER_H_

/// @file
/// Defines Logger interface.


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


namespace fredcpp {
namespace internal {


/// Logging priority level.

struct LogLevel {
  typedef enum {
      LOG_NULL = 0
      , LOG_INFO
      , LOG_WARN
      , LOG_ERROR
      , LOG_FATAL
      , LOG_DEBUG
      , maxLevel
  } Level;

  static bool valid(const Level level);
};

//______________________________________________________________________________


/// Logging context.

struct LogContext {
  const char* file;
  long line;
  const char* func;

  LogContext(const char* file_, const long line_, const char* func_);

private:
  static const char* UNKNOWN_;
};

//______________________________________________________________________________


/// Logger interface.
/// Logs a message of specified priority level with additional context details.
/// Supports selective togglig of enabled logging priority levels.
///
/// Implement this interface for the specific external logging framework used.

class Logger {
public:
  Logger();
  virtual ~Logger();

  /// Logs a message of specified priority level.
  virtual void logMessage(LogLevel::Level level, const std::string& message, const LogContext& context) = 0;

  /// @{
  /** Toggles logging of specified priority level.
  */
  virtual bool enableLevel(internal::LogLevel::Level level) = 0;
  virtual bool disableLevel(internal::LogLevel::Level level) = 0;
  /// @}

  /// Tests if logging is enabled for specified priority level.
  virtual bool levelEnabled(LogLevel::Level level) const = 0;


private:
  Logger(const Logger&);
  Logger& operator= (const Logger&);
};


} // namespace internal
} // namespace fredcpp

//______________________________________________________________________________


/// @name Function Context
/// Define magic macros for function name, useful to specify source context.
/// Some compilers do not define `__func__` macro (standard in C99).\n
/// Also some compilers define macro for "pretty" name (includes class name etc.)
///
/// @attention Platform specific.
/// @{

#ifndef __func__
# ifdef __FUNCTION__
#  define __func__ __FUNCTION__
# endif
#endif /* __func__ */

#ifdef __func__
# define FREDCPP__FUNC__ __func__
#else
# define FREDCPP__FUNC__ "<unknown>"
#endif /* __func__ */

#ifdef __PRETTY_FUNCTION__
# define FREDCPP__PRETTY_FUNC__ __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
# define FREDCPP__PRETTY_FUNC__ __FUNCSIG__
#else
# define FREDCPP__PRETTY_FUNC__ FREDCPP__FUNC__
#endif

/// @}


#endif  // FREDCPP_INTERNAL_LOGGER_H_
