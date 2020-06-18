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

#include <fredcpp/ApiResponse.h>

namespace fredcpp {


internal::KeyValueMap::mapped_type ApiEntity::attribute(const internal::KeyValueMap::key_type& name) const {
  internal::KeyValueMap::mapped_type nullValue;
  internal::KeyValueMap::mapped_type& value(nullValue);

  internal::KeyValueMap::const_iterator itFound;

  itFound = attributes.find(name);
  if (itFound != attributes.end()) {
    value = itFound->second;
  }

  return (value);
}


std::ostream& ApiEntity::print(std::ostream& os) const {
  // name:{attribute=val|...|value}

  os << name << ":{";

  for (internal::KeyValueMap::const_iterator it = attributes.begin();
       it != attributes.end();
       ++it) {
    os << it->first << "=" << it->second
       << "|";
  }

  os << value << "}";

  return (os);
}


void ApiEntity::clear() {
  name.clear();
  value.clear();
  attributes.clear();
}



std::ostream& operator<< (std::ostream& os, const ApiEntity& object) {
  return (object.print(os));
}

//______________________________________________________________________________

ApiResponse::ApiResponse() {
  clear();
}

bool ApiResponse::good() const {
  return (!error);
}

void ApiResponse::setError(const ApiError& otherError) {
  error = otherError;
}

void ApiResponse::setErrorFromResult() {
  error.clear();

  if (result.name == "error") {
    error.status = ApiError::FREDCPP_ERROR;

    error.code = result.attribute("code");
    error.message = result.attribute("message");

  } else if ( !result.name.empty() ) {
    error.status = ApiError::FREDCPP_SUCCESS;
  }
}


std::ostream& ApiResponse::print(std::ostream& os) const {
  // {result
  // entities.size():[
  //    entity[0]
  //    ...
  // ]
  // }

  const std::string ARRAY_ELEMENT_OFFSET("  ");

  os << "{" << result << std::endl;
  os << entities.size() << ":[" << std::endl;

  for (std::size_t n = 0; n < entities.size(); ++n) {
    os << ARRAY_ELEMENT_OFFSET << entities[n] << std::endl;
  }

  os << "]" << std::endl;
  os << "}";

  return (os);
}


void ApiResponse::clear() {
  error.clear();
  result.clear();
  entities.clear();
}


std::ostream& operator<< (std::ostream& os, const ApiResponse& object) {
  return (object.print(os));
}

} // namespace fredcpp
