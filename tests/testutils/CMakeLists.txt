
project(fredcpp-testutils)

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

set(testutils_SRCS
  fredcpp-testutils.cpp
)

set(FREDCPP_TESTUTILS_LIBRARY testutils
  CACHE INTERNAL "testutils library"
)

include_directories(
  ${FREDCPP_TESTS_INCLUDE_DIRS}
)


add_library(${FREDCPP_TESTUTILS_LIBRARY} STATIC
  ${fredcpp_SRCS}
  ${testutils_SRCS}
)
