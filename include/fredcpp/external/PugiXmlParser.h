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

#ifndef FREDCPP_EXTERNAL_PUGIXMLPARSER_H_
#define FREDCPP_EXTERNAL_PUGIXMLPARSER_H_

/// @file
/// Defines `fredcpp` XML Response Parser Facility for `pugixml` parser.
///
/// @example example1.cpp


#include <fredcpp/internal/XmlResponseParser.h>

#include <fredcpp/third_party/pugixml/pugixml.hpp>


namespace fredcpp {
namespace external {


/// XML Response Parser Facility instance for `pugixml` parser.
///
class PugiXmlParser : public internal::XmlResponseParser {
public:
  ~PugiXmlParser();

  static PugiXmlParser& getInstance();

  bool parse(std::istream& xml, ApiResponse& response);

  /// `pugixml` status.
  pugi::xml_parse_result getParseResult() const;


private:
  PugiXmlParser();

  pugi::xml_parse_result parseResult_;

};

} // namespace external
} // namespace fredcpp

#endif // FREDCPP_EXTERNAL_PUGIXMLPARSER_H_