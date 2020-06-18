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

#include <fredcpp/external/SimpleLogger.h>

#include <cassert>

#include <sstream>
#include <string>


namespace fredcpp {
namespace external {

LogChannel::LogChannel(internal::LogLevel::Level level, std::ostream& os)
  : level_(level)
  , osPtr_(&os) {
  enable();
}


void LogChannel::writeLine(const std::string& str) {
  if (enabled_) {
    (*osPtr_) << str
              << std::endl;
  }
}


bool LogChannel::enable() {
  bool wasEnabled(enabled_);
  enabled_ = ( !isNull() );
  return (wasEnabled);
}


bool LogChannel::disable() {
  bool wasEnabled(enabled_);
  enabled_ = false;
  return (wasEnabled);
}


void LogChannel::setOutput(std::ostream& os) {
  osPtr_ = &os;
}


void LogChannel::setLevel(internal::LogLevel::Level level) {
  level_ = level;
}


internal::LogLevel::Level LogChannel::getLevel() const {
  return (level_);
}


bool LogChannel::enabled() const {
  return (enabled_);
}


bool LogChannel::isNull() const {
  return (internal::LogLevel::LOG_NULL == level_);
}


//______________________________________________________________________________

LogFile::LogFile() {
}


LogFile::LogFile(const std::string& path)
  : path_(path) {
}


LogFile::~LogFile() {
  close();
}


bool LogFile::openNew(const std::string& path) {
  close();
  path_ = path;
  return (open(std::ios::trunc));
}


bool LogFile::openForAppend(const std::string& path) {
  close();
  path_ = path;
  return (open(std::ios::app));
}


void LogFile::close() {
  if (ofs_.is_open()) {
    ofs_.close();
  }
  path_.clear();
}


std::ofstream& LogFile::useStream() {
  return (ofs_);
}


const std::string& LogFile::getPath() const {
  return (path_);
}


bool LogFile::isOpen() const {
  return (ofs_.is_open());
}


bool LogFile::open(std::ios_base::openmode mode) {
  //requireValidPath
  ofs_.open(path_.c_str(), mode);
  return(ofs_.good());
}


//______________________________________________________________________________

SimpleLogger::SimpleLogger() {
  setupChannel(internal::LogLevel::LOG_INFO);
  setupChannel(internal::LogLevel::LOG_WARN);
  setupChannel(internal::LogLevel::LOG_ERROR);
  setupChannel(internal::LogLevel::LOG_FATAL);
  setupChannel(internal::LogLevel::LOG_DEBUG);


  // Default config
  // - enable WARN, ERROR, FATAL
  // - disable INFO and DEBUG
  // - output to std::cerr, INFO to std::cout

  enableLevel(internal::LogLevel::LOG_WARN);
  enableLevel(internal::LogLevel::LOG_ERROR);
  enableLevel(internal::LogLevel::LOG_FATAL);

  disableLevel(internal::LogLevel::LOG_INFO);
  disableLevel(internal::LogLevel::LOG_DEBUG);

  setOutput(std::cerr);
  setOutput(internal::LogLevel::LOG_INFO, std::cout);

  formatter_ = defaultLogFormat;

}


SimpleLogger::~SimpleLogger() {
}


SimpleLogger& SimpleLogger::getInstance() {
  static SimpleLogger instance;
  return (instance);
}


void SimpleLogger::logMessage(internal::LogLevel::Level level, const std::string& message, const internal::LogContext& context) {
  LogChannel& channel = useChannel(level);

  if (!channel.enabled()) {
    return;
  }

  std::ostringstream buf;
  formatMessage(buf, channel.getLevel(), message, context);

  channel.writeLine(buf.str());
}


void SimpleLogger::setOutput(internal::LogLevel::Level level, std::ostream& os) {
  LogChannel& channel = useChannel(level);
  LogFile& file = useFile(level);

  if (file.useStream() != os ) {
    file.close();
  }

  channel.setOutput(os);
}


void SimpleLogger::setOutput(internal::LogLevel::Level level, const std::string& path) {
  LogChannel& channel = useChannel(level);

  // First check if path has already been opened and then use its stream
  // otherwise open new file

  LogFile* foundFilePtr = findFile(path);

  if (foundFilePtr) {
    LogFile& foundFile = *foundFilePtr;

    setOutput(level, foundFile.useStream());

  } else {
    LogFile& file = useFile(level);

    file.close();

    file.openNew(path);
    setOutput(level, file.useStream());
  }

}


void SimpleLogger::setOutput(std::ostream& os) {
  // Set all enabled channels to write to the same stream

  std::size_t numChannels = sizeof(channels_) / sizeof(channels_[0]);

  for (std::size_t n = 0; n < numChannels; ++n) {
    LogChannel& channel = channels_[n];

    if (channel.getLevel() != getNullChannel().getLevel()) {
      setOutput(channel.getLevel(), os);
    }
  }
}


void SimpleLogger::setOutput(const std::string& path) {
  // Set all enabled channels to write to the same file.
  // first set LOG_INFO channel to the path,
  // then use its file stream to set the others

  LogChannel& infoChannel = useChannel(internal::LogLevel::LOG_INFO);
  setOutput(internal::LogLevel::LOG_INFO, path);

  LogFile& infoFile = useFile(internal::LogLevel::LOG_INFO);

  std::size_t numChannels = sizeof(channels_) / sizeof(channels_[0]);

  for (std::size_t n = 0; n < numChannels; ++n) {
    LogChannel& channel = channels_[n];

    if (channel.getLevel() != getNullChannel().getLevel()
        && channel.getLevel() != infoChannel.getLevel()) {
      setOutput(channel.getLevel(), infoFile.useStream());
    }
  }
}


void SimpleLogger::setFormatter(SimpleLogger::LogFormatter formatter) {
  formatter_ = formatter;
}


bool SimpleLogger::levelEnabled(internal::LogLevel::Level level) const {
  const LogChannel& channel = getChannel(level);
  return (channel.enabled());
}


bool SimpleLogger::enableLevel(internal::LogLevel::Level level) {
  LogChannel& channel = useChannel(level);
  return (channel.enable());
}


bool SimpleLogger::disableLevel(internal::LogLevel::Level level) {
  LogChannel& channel = useChannel(level);
  return (channel.disable());
}


bool SimpleLogger::enableInfo() {
  return (enableLevel(internal::LogLevel::LOG_INFO));
}


bool SimpleLogger::enableWarn() {
  return (enableLevel(internal::LogLevel::LOG_WARN));
}


bool SimpleLogger::enableError() {
  return (enableLevel(internal::LogLevel::LOG_ERROR));
}


bool SimpleLogger::enableFatal() {
  return (enableLevel(internal::LogLevel::LOG_FATAL));
}


bool SimpleLogger::enableDebug() {
  return (enableLevel(internal::LogLevel::LOG_DEBUG));
}


bool SimpleLogger::disableInfo() {
  return (disableLevel(internal::LogLevel::LOG_INFO));
}


bool SimpleLogger::disableWarn() {
  return (disableLevel(internal::LogLevel::LOG_WARN));
}


bool SimpleLogger::disableError() {
  return (disableLevel(internal::LogLevel::LOG_ERROR));
}


bool SimpleLogger::disableFatal() {
  return (disableLevel(internal::LogLevel::LOG_FATAL));
}


bool SimpleLogger::disableDebug() {
  return (disableLevel(internal::LogLevel::LOG_DEBUG));
}


void SimpleLogger::setupChannel(internal::LogLevel::Level level) {
  LogChannel& channel(useChannel(level));
  channel.setLevel(level);
  channel.enable();
}


LogChannel& SimpleLogger::useChannel(internal::LogLevel::Level level) {
  LogChannel& channel(const_cast<LogChannel&>(getChannel(level)));
  return (channel);
}


LogFile& SimpleLogger::useFile(internal::LogLevel::Level level) {
  const LogChannel& channel(getChannel(level));
  LogFile& file(files_[static_cast<std::size_t>(level)]);
  return (file);
}


LogFile* SimpleLogger::findFile(const std::string& path) {
  LogFile* foundFile(NULL);

  std::size_t numFiles = sizeof(files_) / sizeof(files_[0]);

  for (std::size_t n = 0; n < numFiles; ++n) {
    LogFile& file = files_[n];

    // case-sensitive match
    if (file.getPath() == path) {
      foundFile = &file;
      break;
    }
  }

  return (foundFile);
}


const LogChannel& SimpleLogger::getNullChannel() const {
  const LogChannel& nullChannel = channels_[static_cast<std::size_t>(internal::LogLevel::LOG_NULL)];
  return (nullChannel);
}


const LogChannel& SimpleLogger::getChannel(internal::LogLevel::Level level) const {

  if (!requireValidLevel(level)) {
    assert( requireValidLevel(level) && "Valid log-level expected");
    return (getNullChannel());  // error
  }

  const LogChannel& channel(channels_[static_cast<std::size_t>(level)]);
  return (channel);
}


std::ostream& SimpleLogger::formatMessage(std::ostream& os, internal::LogLevel::Level level, const std::string& message, const internal::LogContext& context) {

  if (formatter_ == NULL) {
    os << message;

  } else {
    formatter_(os, level, message, context);
  }

  return (os);
}


bool SimpleLogger::requireValidLevel(internal::LogLevel::Level level) const {
  return (internal::LogLevel::valid(level));
}


//______________________________________________________________________________

std::ostream& defaultLogFormat(std::ostream& os, internal::LogLevel::Level level, const std::string& message, const internal::LogContext& context) {
  bool requireValidOutput(os.good());
  if (!requireValidOutput) {
    assert(requireValidOutput && "Valid output stream expected");
    return (os);
  }

  switch (level) {
  case internal::LogLevel::LOG_INFO:
    os << "I"
       << "|" << message;
    break;

  case internal::LogLevel::LOG_WARN:
    os << "W"
       << "|" << message;
    break;

  case internal::LogLevel::LOG_ERROR:
    os << "E"
       << "|" << message;
    break;

  case internal::LogLevel::LOG_FATAL:
    os << "F"
       << "|" << message;
    break;

  case internal::LogLevel::LOG_DEBUG:
    os << "DBG"
       << ":[" << context.file << ":" << context.line  << " (" << context.func << ")]"
       << "|" << message;
    break;

  default:
    assert(false && "Valid log-level expected");
  }

  return (os);
}


} // namespace external
} // namespace fredcpp
