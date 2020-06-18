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

#ifndef FREDCPP_MOCKXMLPARSER_H_
#define FREDCPP_MOCKXMLPARSER_H_

#include <fredcpp/ApiResponse.h>

#include <fredcpp/internal/XmlResponseParser.h>


namespace fredcpp {

class MockXmlParser : public internal::XmlResponseParser {
public:
  typedef enum {
    MOCK_OK = 0,
    MOCK_ERROR,
    MOCK_FAIL,
  } ParseMode;

  static MockXmlParser& getInstance() {
    static MockXmlParser instance;
    return (instance);
  }

  virtual bool parse(std::istream& xml, ApiResponse& response);

  MockXmlParser& withParseMode(ParseMode mode) {
    parseMode_ = mode;
    return (*this);
  }

private:
  MockXmlParser()
    : parseMode_(MOCK_OK) {
  }

  bool parse_OK(std::istream& xml, ApiResponse& response);
  bool parse_ERROR(std::istream& xml, ApiResponse& response);
  bool parse_FAIL(std::istream& xml, ApiResponse& response);

  ParseMode parseMode_;
};


} // namespace fredcpp


//______________________________________________________________________________
// Implementation of XmlResponseParser interface

namespace fredcpp {

inline bool MockXmlParser::parse(std::istream& xml, ApiResponse& response) {
  bool result(false);

  switch (parseMode_) {
  case MOCK_OK:
    result = parse_OK(xml, response);
    break;

  case MOCK_ERROR:
    result = parse_ERROR(xml, response);
    break;

  case MOCK_FAIL:
    result = parse_FAIL(xml, response);
    break;

  default:
    assert(false && "Unsupported ParseMode");
  }

  return (result);
}


inline bool MockXmlParser::parse_OK(std::istream& xml, ApiResponse& response) {
  bool result(false);

  response.clear();

  response.result.name = "seriess";

  ApiEntity entity;
  entity.name = "series";
  entity.attributes["id"] = "TEST-ID";
  response.entities.push_back(entity);

  result = true;
  return (result);
}


inline bool MockXmlParser::parse_ERROR(std::istream& xml, ApiResponse& response) {
  bool result(false);

  response.clear();

  response.result.name = "error";
  response.result.attributes["code"] = "400";
  response.result.attributes["message"] = "Bad Request.  Error description.";

  result = true;
  return (result);
}


inline bool MockXmlParser::parse_FAIL(std::istream& xml, ApiResponse& response) {
  bool result(false);

  response.clear();

  result = false;
  return (result);
}


} // namespace fredcpp


#endif // FREDCPP_MOCKXMLPARSER_H_

