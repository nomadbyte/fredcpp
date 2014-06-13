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

#include <fredcpp-testutils.h>


namespace fredcpp {
namespace test {

std::string harmonizePath(const std::string& path) {
  std::string result(path);

  if (path.empty()) {
    return (result);
  }

  // replace path-separator to match the platform-specific

#ifdef _WIN32
  const std::string& search = "/";
  const std::string& replaceWith = "\\";
#else
  const std::string& search = "\\";
  const std::string& replaceWith = "/";
#endif

  size_t pos = 0;

  while ((pos = result.find(search, pos)) != std::string::npos) {
    result.replace(pos, search.length(), replaceWith);
    pos += replaceWith.length();
  }

  return (result);
}

} // namespace test
} // namespace fredcpp
