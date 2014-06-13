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

#ifndef FREDCPP_INTERNAL_REQUEST_H_
#define FREDCPP_INTERNAL_REQUEST_H_

/// @file
/// Defines a generic request object.


#include <fredcpp/internal/utils.h>

#include <ostream>
#include <string>


namespace fredcpp {
namespace internal {


/// Generic request.
/// Manages a collection of parameters (key-values).
///
/// @attention Currently only one value type is supported.


class Request {
public:
  Request();
  Request(const Request& other);
  virtual ~Request();

  Request& operator= (const Request& rhs);
  void swap(Request& other);

  /// Sets specified parameter value, adds it if the parameter does not exist.
  Request& with(const KeyValueMap::key_type& key, const KeyValueMap::mapped_type& value);

  /// Gets value of the specified parameter.
  KeyValueMap::mapped_type operator[] (const KeyValueMap::key_type& key) const;

  /// Removes the specified parameter.
  void eraseParam(const KeyValueMap::key_type& key);

  /// Tests whether specified parameter exists.
  bool hasParam(const KeyValueMap::key_type& key) const;

  /// Returns reference to the parameter collection.
  const KeyValueMap& getParams() const;

  /// Removes all parameters.
  virtual void clear();

  /// Prints parameters in formatted form.
  virtual std::ostream& print(std::ostream& os) const;


protected:
  /// Resets parameters from an external collection.
  void setParams(const KeyValueMap& params);


private:
  /// Stores parameter value, adds it if the parameter does not exist.
  void insertParam(const KeyValueMap::key_type& key, const KeyValueMap::mapped_type& value);


  KeyValueMap params_;
};

//______________________________________________________________________________

std::ostream& operator<< (std::ostream& os, const Request& object);


} // namespace internal
} // namespace fredcpp


//______________________________________________________________________________

namespace std {

template<>
inline void swap(fredcpp::internal::Request& lhs, fredcpp::internal::Request& rhs) {
  lhs.swap(rhs);
}

} // namespace std


#endif // FREDCPP_INTERNAL_REQUEST_H_
