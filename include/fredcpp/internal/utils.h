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

#ifndef FREDCPP_INTERNAL_UTILS_H_
#define FREDCPP_INTERNAL_UTILS_H_

/// @file
/// Defines various utility functions.


#include <map>
#include <algorithm>
#include <string>

namespace fredcpp {
namespace internal {


/// String key-value collection.
/// Unique keys expected - matching is case-insensitive.\n
/// Only one value per key.
///
/// @attention Currently only string values are supported

struct lessNoCase;  // forward
typedef std::map<std::string, std::string, lessNoCase> KeyValueMap;



/// Case-insensitive string compare functor.

struct lessNoCase : public std::binary_function<std::string, std::string, bool> {

  /// less functor for case-insensitive comparison

  struct less_nocase : public std::binary_function<unsigned char, unsigned char, bool> {
    bool operator() (const unsigned char& c1, const unsigned char& c2) const {
        return tolower (c1) < tolower (c2);
    }
  };


  /// Compares two strings disregarding the case of characters.
  /// @return true when first string evaluates less than the second string.
  bool operator() (const std::string & s1, const std::string & s2) const {
    return std::lexicographical_compare (
        s1.begin(), s1.end(),
        s2.begin(), s2.end(),
        less_nocase()
        );
  }
};


/// Sleep for number of seconds.
/// Suspends execution of the current process for specified number of seconds.
void sleep(unsigned secs);



} // namespace fredcpp
} // namespace internal

#endif // FREDCPP_INTERNAL_UTILS_H_