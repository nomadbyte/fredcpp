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

#ifndef FREDCPP_VERSION_H_
#define FREDCPP_VERSION_H_

/// @file
/// Defines `fredcpp` release version.



/// @name Facility
/// `fredcpp` facility description.
/// @{
#define FREDCPP_FACILITY  "${fredcpp_FACILITY}"
#define FREDCPP_BRIEF  "${fredcpp_BRIEF}"
/// @}


/// @anchor FREDCPP_VERSION
/// @name Release Version
/// `fredcpp` release version.
/// @{
#define FREDCPP_VERSION_MAJOR  ${fredcpp_VERSION_MAJOR}
#define FREDCPP_VERSION_MINOR  ${fredcpp_VERSION_MINOR}
#define FREDCPP_VERSION_PATCH  ${fredcpp_VERSION_PATCH}

#define FREDCPP_VERSION_STRING "${fredcpp_VERSION_STRING}"
/// @}



// version helper macros
//
#define FREDCPP_VERSION_INT(a, b, c) ((a) << 16 | (b) << 8 | (c))


/// Version number.
#define FREDCPP_VERSION FREDCPP_VERSION_INT(FREDCPP_VERSION_MAJOR, \
                                       FREDCPP_VERSION_MINOR, \
                                       FREDCPP_VERSION_PATCH)

#endif // FREDCPP_VERSION_H_