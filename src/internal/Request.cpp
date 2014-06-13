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

#include <fredcpp/internal/Request.h>


namespace fredcpp {
namespace internal {


Request::Request() {

}


Request::Request(const Request& other) {
  params_ = other.params_;
}


Request::~Request() {
}


void Request::swap(Request& other) {
  using std::swap;
  params_.swap(other.params_);
}


Request& Request::operator= (const Request& rhs) {
  Request req(rhs);

  using std::swap;
  swap(*this, req);

  return (*this);
}


Request& Request::with(const KeyValueMap::key_type& key, const KeyValueMap::mapped_type& value) {
  insertParam(key, value);
  return (*this);
}


KeyValueMap::mapped_type Request::operator[] (const KeyValueMap::key_type& key) const {
  KeyValueMap::mapped_type defaultValue;

  KeyValueMap::const_iterator itFound(params_.find(key));

  if (itFound == params_.end()) {
    return (defaultValue);
  }

  return (itFound->second);
}


void Request::eraseParam(const KeyValueMap::key_type& key) {
  KeyValueMap::iterator itFound(params_.find(key));

  if (itFound != params_.end()) {
    params_.erase(itFound);
  }
}


bool Request::hasParam(const KeyValueMap::key_type& key) const {
  KeyValueMap::const_iterator itFound(params_.find(key));

  return (itFound != params_.end());
}


const KeyValueMap& Request::getParams() const {
  return (params_);
}


void Request::clear() {
  params_.clear();
}


std::ostream& Request::print(std::ostream& os) const {
  // key=val|...|

  for (KeyValueMap::const_iterator it = params_.begin();
       it != params_.end();
       ++it) {
    os << it->first << "=" << it->second
       << "|";
  }

  return (os);
}


void Request::setParams(const KeyValueMap& params) {
  params_ = params;
}


void Request::insertParam(const KeyValueMap::key_type& key, const KeyValueMap::mapped_type& value) {
  params_[key] = value;
}


std::ostream& operator<< (std::ostream& os, const Request& object) {
  return (object.print(os));
}

} // namespace internal
} // namespace fredcpp
