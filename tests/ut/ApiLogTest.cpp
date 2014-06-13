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

#include <fredcpp-gtest.h>
#include <gtest/gtest.h>

#include <fredcpp/ApiLog.h>

#include <MockLogger.h>


TEST(ApiLog, IsSingleInstance) {
  FREDCPP_TESTCASE("Exists as a single instance only");
  using namespace fredcpp;

  //ApiLog badLog; // FAILS-COMPILE:uncomment to test

  ApiLog& log = ApiLog::getInstance();
}

TEST(ApiLog, RequiresValidLogger) {
  FREDCPP_TESTCASE("Requires pointer to a valid Logger implementation");
  using namespace fredcpp;

  ApiLog& log = ApiLog::getInstance();

  //log.info("message",FREDCPP_LOGCONTEXT); // FAILS-ASSERT:uncomment to test

  MockLogger& logger (MockLogger::getInstance());
  log.configure().withLogger(&logger);
  log.info("message",FREDCPP_LOGCONTEXT);
}

TEST(ApiLog, ForwardsLoggingToggleToLogger) {
  FREDCPP_TESTCASE("Logging toggle forwarded to Logger object");
  using namespace fredcpp;

  MockLogger& logger (MockLogger::getInstance());
  ApiLog& log = ApiLog::getInstance().configure()
                                     .withLogger(&logger);

  ASSERT_EQ(logger.levelEnabled(internal::LogLevel::LOG_INFO), log.infoEnabled());
  logger.enableLevel(internal::LogLevel::LOG_INFO);
  ASSERT_TRUE(log.infoEnabled());

  ASSERT_EQ(logger.levelEnabled(internal::LogLevel::LOG_WARN), log.warnEnabled());
  logger.enableLevel(internal::LogLevel::LOG_WARN);
  ASSERT_TRUE(log.warnEnabled());

  ASSERT_EQ(logger.levelEnabled(internal::LogLevel::LOG_ERROR), log.errorEnabled());
  logger.enableLevel(internal::LogLevel::LOG_ERROR);
  ASSERT_TRUE(log.errorEnabled());

  ASSERT_EQ(logger.levelEnabled(internal::LogLevel::LOG_FATAL), log.fatalEnabled());
  logger.enableLevel(internal::LogLevel::LOG_FATAL);
  ASSERT_TRUE(log.fatalEnabled());

  ASSERT_EQ(logger.levelEnabled(internal::LogLevel::LOG_DEBUG), log.debugEnabled());
  logger.enableLevel(internal::LogLevel::LOG_DEBUG);
  ASSERT_TRUE(log.debugEnabled());
}

TEST(ApiLog, ForwardsLogMessageToLogger) {
  FREDCPP_TESTCASE("Log message is forwarded to Logger object");
  using namespace fredcpp;

  MockLogger& logger (MockLogger::getInstance());
  ApiLog& log = ApiLog::getInstance().configure()
                                     .withLogger(&logger);

  logger.enableLevel(internal::LogLevel::LOG_INFO);
  logger.enableLevel(internal::LogLevel::LOG_WARN);
  logger.enableLevel(internal::LogLevel::LOG_ERROR);
  logger.enableLevel(internal::LogLevel::LOG_FATAL);
  logger.enableLevel(internal::LogLevel::LOG_DEBUG);

  log.info("info-message", FREDCPP_LOGCONTEXT);
  ASSERT_EQ("info-message", logger.getInfo());

  log.warn("warn-message", FREDCPP_LOGCONTEXT);
  ASSERT_EQ("warn-message", logger.getWarn());

  log.error("error-message", FREDCPP_LOGCONTEXT);
  ASSERT_EQ("error-message", logger.getError());

  log.fatal("fatal-message", FREDCPP_LOGCONTEXT);
  ASSERT_EQ("fatal-message", logger.getFatal());

  log.debug("debug-message", FREDCPP_LOGCONTEXT);
  ASSERT_EQ("debug-message", logger.getDebug());
}


TEST(ApiLog, HelperMacrosTest) {
  FREDCPP_TESTCASE("Helper macros allow log-message with stream syntax");
  using namespace fredcpp;

  MockLogger& logger (MockLogger::getInstance());
  ApiLog& log = ApiLog::getInstance().configure()
                                     .withLogger(&logger);

  logger.enableLevel(internal::LogLevel::LOG_INFO);
  logger.enableLevel(internal::LogLevel::LOG_WARN);
  logger.enableLevel(internal::LogLevel::LOG_ERROR);
  logger.enableLevel(internal::LogLevel::LOG_FATAL);
  logger.enableLevel(internal::LogLevel::LOG_DEBUG);

  FREDCPP_LOG_INFO("info-message:" << 1 << "|test");
  ASSERT_EQ("info-message:1|test", logger.getInfo());

  FREDCPP_LOG_WARN("warn-message:" << 1 << "|test");
  ASSERT_EQ("warn-message:1|test", logger.getWarn());

  FREDCPP_LOG_ERROR("error-message:" << 1 << "|test");
  ASSERT_EQ("error-message:1|test", logger.getError());

  FREDCPP_LOG_FATAL("fatal-message:" << 1 << "|test");
  ASSERT_EQ("fatal-message:1|test", logger.getFatal());

  FREDCPP_LOG_DEBUG("debug-message:" << 1 << "|test");
  ASSERT_EQ("debug-message:1|test", logger.getDebug());
}

TEST(ApiLog, AllowsDebugDepth) {
  FREDCPP_TESTCASE("Allows control of debug verbosity. Suppress debug messages > allowed depth");
  using namespace fredcpp;

  MockLogger& logger (MockLogger::getInstance());
  ApiLog& log = ApiLog::getInstance().configure()
                                     .withLogger(&logger)
                                     .withDebugDepth(0);

  logger.enableLevel(internal::LogLevel::LOG_DEBUG);

  FREDCPP_LOG_DEBUG("debug:0");
  ASSERT_EQ("debug:0", logger.getDebug());

  FREDCPP_LOG_DBGN(1, "debug:1");  // Debug:suppressed
  ASSERT_NE("debug:1", logger.getDebug());


  // increase allowed debug depth
  log.withDebugDepth(1);

  FREDCPP_LOG_DBGN(1, "debug:1");  // Debug:printed
  ASSERT_EQ("debug:1", logger.getDebug());
}
