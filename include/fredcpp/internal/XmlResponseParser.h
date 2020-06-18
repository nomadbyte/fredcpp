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

#ifndef FREDCPP_INTERNAL_XMLRESPONSEPARSER_H_
#define FREDCPP_INTERNAL_XMLRESPONSEPARSER_H_

/// @file
/// Defines XML Response Parser Facility interface.


#include <istream>

namespace fredcpp {

struct ApiResponse; // forward


namespace internal {

/// XML Response Parser Facility interface.
/// Parses content of the supplied XML stream into ApiResponse object.
///
/// Implement this interface for the specific XML parser used.

class XmlResponseParser {
public:
  XmlResponseParser();
  virtual ~XmlResponseParser();

  /// Parses the supplied XML stream into ApiResponse object.
  virtual bool parse(std::istream& xml, ApiResponse& response) = 0;

};

} // namespace internal
} // namespace fredcpp

#endif // FREDCPP_INTERNAL_XMLRESPONSEPARSER_H_