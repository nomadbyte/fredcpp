
project(fredcpp)

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

## cmake includes
##
set(CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake"
  "${CMAKE_SOURCE_DIR}/cmake/Modules"
  ${CMAKE_SOURCE_DIR}
)


## facility version
##
include(DefineFacilityVersion)


## application
##
set(APPLICATION_NAME ${${PROJECT_NAME}_FACILITY})
set(APPLICATION_BRIEF ${${PROJECT_NAME}_BRIEF})

set(APPLICATION_VERSION_MAJOR ${${APPLICATION_NAME}_VERSION_MAJOR})
set(APPLICATION_VERSION_MINOR ${${APPLICATION_NAME}_VERSION_MINOR})
set(APPLICATION_VERSION_PATCH ${${APPLICATION_NAME}_VERSION_PATCH})

set(APPLICATION_VERSION ${${APPLICATION_NAME}_VERSION_STRING})


set(LIBRARY_VERSION APPLICATION_VERSION)
set(LIBRARY_SOVERSION APPLICATION_VERSION_MAJOR)


## definitions
##
include(DefineCMakeDefaults)
include(DefinePlatform)
include(DefineCompilerFlags)
include(DefineInstallationPaths)
include(WithOptions)
include(ConfigureChecks)


## disallow in-source build
##
include(MacroEnsureOutOfSourceBuild)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out-of-source build. Please create a separate build directory and run 'cmake /path/to/${PROJECT_NAME} [options]' there.")


## check external dependencies
##
if (WITH_CURL)
  find_package(CURL REQUIRED)
endif (WITH_CURL)


## components
##
add_subdirectory(third_party)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(doc)



## tests
##
## enable_testing() on the top-level to enable make test target
## OR include CTest for full-blown test support
##
if (WITH_TESTS)
  include(DefineApiKey)
  enable_testing()
  #include(CTest)
  add_subdirectory(tests)
endif (WITH_TESTS)

## examples
##
if (WITH_EXAMPLES)
  add_subdirectory(examples)
endif (WITH_EXAMPLES)


## Add uninstall target

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/cmake/CMakeUninstall.cmake
)


## report

message("---------------------------------------------")
message("BUILD:${APPLICATION_NAME}-${APPLICATION_VERSION} ${CMAKE_BUILD_TYPE}")

message("Http-client:${FREDCPP_BUILD_HTTP_CLIENT}")
message("  CURL:${WITH_CURL}")

message("Xml-parser:${FREDCPP_BUILD_XML_PARSER}")
message("  pugixml:${WITH_PUGIXML}")

message("Logger:${FREDCPP_BUILD_LOGGER}")
message("  SimpleLogger:${WITH_SIMPLELOGGER}")

message("Testing:${WITH_TESTS}")
if (WITH_TESTS)
  message("  gtest-at options:'${FREDCPP_GTEST_AT_OPTIONS}'")
  message("  gtest-ut options:'${FREDCPP_GTEST_UT_OPTIONS}'")
  message("  FRED API key file:'${FREDCPP_API_KEY_FILE}'")
endif (WITH_TESTS)

message("Examples:${WITH_EXAMPLES}")

message("---------------------------------------------")

