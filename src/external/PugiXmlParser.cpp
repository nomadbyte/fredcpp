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

#include <fredcpp/external/PugiXmlParser.h>

#include <fredcpp/ApiResponse.h>


namespace fredcpp {
namespace external {

PugiXmlParser::PugiXmlParser() {
}

PugiXmlParser::~PugiXmlParser() {
}

PugiXmlParser& PugiXmlParser::getInstance() {
  static PugiXmlParser instance;

  return (instance);
}

bool PugiXmlParser::parse(std::istream& xml, ApiResponse& response) {
  bool result(false);

  pugi::xml_document doc;

  parseResult_ = doc.load(xml);

  //check error
  if (!parseResult_) {
    // error
    return (result);
  }

  pugi::xml_node resultNode = doc.first_child();  // should be only one result container

  //TODO:check if valid resultNode

  response.result.name = resultNode.name();

  pugi::xml_attribute_iterator ait;

  // get result attributes
  for ( ait = resultNode.attributes_begin();
        ait != resultNode.attributes_end();
        ++ait) {
    response.result.attributes[ait->name()] = ait->value();
  }

  pugi::xml_node_iterator it;

  ApiEntity entity;

  // get entities
  for ( it = resultNode.begin();
        it != resultNode.end();
        ++it) {

    entity.clear();

    // get node and it's first data
    entity.name = it->name();
    entity.value = it->child_value();

    // get attributes
    for (ait = it->attributes_begin();
         ait != it->attributes_end();
         ++ait) {
      entity.attributes[ait->name()] = ait->value();
    }

    response.entities.push_back(entity);
  }

  result = true;

  return (result);
}

pugi::xml_parse_result PugiXmlParser::getParseResult() const {
  return (parseResult_);
}


} // namespace external
} // namespace fredcpp
