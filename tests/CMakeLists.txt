
project(tests)

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

if (WITH_CURL AND CURL_FOUND)
  set(FREDCPP_PUBLIC_INCLUDE_DIRS
    ${FREDCPP_PUBLIC_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
  )

  set(FREDCPP_LINK_LIBRARIES
    ${FREDCPP_LINK_LIBRARIES}
    ${CURL_LIBRARIES}
  )
endif (WITH_CURL AND CURL_FOUND)

if (WITH_PUGIXML)
  set(FREDCPP_PUBLIC_INCLUDE_DIRS
    ${FREDCPP_PUBLIC_INCLUDE_DIRS}
    ${PUGIXML_INCLUDE_DIRS}
  )
endif (WITH_PUGIXML)

if (WITH_SIMPLELOGGER)
  set(FREDCPP_PUBLIC_INCLUDE_DIRS
    ${FREDCPP_PUBLIC_INCLUDE_DIRS}
    ${SIMPLELOGGER_INCLUDE_DIRS}
  )
endif (WITH_SIMPLELOGGER)


set(FREDCPP_TESTS_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  CACHE INTERNAL "fredcpp tests include dirs"
)

include_directories(
  ${FREDCPP_TESTS_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
  ${FREDCPP_PUBLIC_INCLUDE_DIRS}
  ${CMAKE_BINARY_DIR}
)


set(FREDCPP_DBG_LINK_LIBRARIES)
if (UNIX)
  set(FREDCPP_DBG_LINK_LIBRARIES
    rt
  )
endif (UNIX)


add_subdirectory(testutils)

## unitTests
add_subdirectory(ut)

## acceptanceTests
set(fredcpp_at_SRCS
  fredcpp-test.cpp
)


add_executable(run-gtest-at ${fredcpp_at_SRCS})
target_link_libraries(run-gtest-at
  ${FREDCPP_STATIC_LIBRARY}
  ${FREDCPP_LINK_LIBRARIES}
  ${FREDCPP_TESTUTILS_LIBRARY}
  ${FREDCPP_DBG_LINK_LIBRARIES}
  ${GTEST_LINK_LIBRARIES}
)


## copy test data, API key, and CA cert file

add_custom_target(testdata-at ALL
  COMMAND "${CMAKE_COMMAND}" -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:run-gtest-at>/data
  COMMAND "${CMAKE_COMMAND}" -E copy_if_different
    ${FREDCPP_API_KEY_FILE} $<TARGET_FILE_DIR:run-gtest-at>/data
  COMMAND "${CMAKE_COMMAND}" -E copy_if_different
    ${FREDCPP_CACERT_FILE} $<TARGET_FILE_DIR:run-gtest-at>/data
)


set(FREDCPP_GTEST_AT_OPTIONS "--gtest_filter=-*.ErrorWhenRealtimeEndAfter*"
  CACHE STRING "gtest options used with acceptance testing."
)

add_test(NAME acceptanceTests
  COMMAND ${CMAKE_COMMAND} -E chdir "$<TARGET_FILE_DIR:run-gtest-at>"
    "$<TARGET_FILE:run-gtest-at>" ${FREDCPP_GTEST_AT_OPTIONS}
)

set_tests_properties(acceptanceTests PROPERTIES
  DEPENDS "unitTests"
)

#set_property(TEST acceptanceTests APPEND PROPERTY
#  DEPENDS unitTests)
#set_tests_properties(acceptanceTest PROPERTIES DEPENDS "unitTests;moreTests")

add_custom_target(check COMMAND "${CMAKE_CTEST_COMMAND}" DEPENDS run-gtest-at)
