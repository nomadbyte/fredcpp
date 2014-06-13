
project(fredcpp-unittests)

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

set(FREDCPP_DBG_LINK_LIBRARIES)
if (UNIX)
  set(FREDCPP_DBG_LINK_LIBRARIES
    rt
  )
endif (UNIX)


set(fredcpp_ut_SRCS
  internal/internalRequestTest.cpp
  internal/internalHttpRequestTest.cpp
  ApiRequestTest.cpp
  ApiResponseTest.cpp
  ApiLogTest.cpp
  ApiTest.cpp

  FredSeriesRequestTest.cpp
  FredReleaseRequestTest.cpp
  FredSourceRequestTest.cpp
  FredCategoryRequestTest.cpp
)


add_executable(run-gtest-ut ${fredcpp_ut_SRCS})
target_link_libraries(run-gtest-ut
  ${FREDCPP_STATIC_LIBRARY}
  ${FREDCPP_LINK_LIBRARIES}
  ${FREDCPP_TESTUTILS_LIBRARY}
  ${FREDCPP_DBG_LINK_LIBRARIES}
  ${GTEST_LINK_LIBRARIES}
)

## copy test data and API key

add_custom_target(testdata-ut ALL
  COMMAND "${CMAKE_COMMAND}" -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:run-gtest-ut>/data
  COMMAND "${CMAKE_COMMAND}" -E copy_if_different
    ${FREDCPP_API_KEY_FILE} $<TARGET_FILE_DIR:run-gtest-ut>/data
)

set(FREDCPP_GTEST_UT_OPTIONS ""
  CACHE STRING "gtest options used with unit testing."
)

add_test(NAME unitTests
  COMMAND ${CMAKE_COMMAND} -E chdir "$<TARGET_FILE_DIR:run-gtest-ut>"
    "$<TARGET_FILE:run-gtest-ut>" ${FREDCPP_GTEST_UT_OPTIONS}
)
