
project(fredcpp-lib)

set(FREDCPP_PUBLIC_INCLUDE_DIRS
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
  CACHE INTERNAL "fredcpp public include directories"
)

set(FREDCPP_LINK_LIBRARIES
  CACHE INTERNAL "fredcpp required libraries"
)

set(FREDCPP_PRIVATE_INCLUDE_DIRS
  ${CMAKE_CURRENT_BINARY_DIR}
)

set(FREDCPP_LINK_LIBRARIES
  ${FREDCPP_REQUIRED_LIBRARIES}
)


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


set(FREDCPP_STATIC_LIBRARY
  fredcpp_static
  CACHE INTERNAL "fredcpp static library"
)

set(fredcpp_SRCS
  Api.cpp
  ApiError.cpp
  ApiLog.cpp
  ApiRequest.cpp
  ApiResponse.cpp
)

set(fredcpp_internal_SRCS
  internal/HttpRequest.cpp
  internal/HttpRequestExecutor.cpp
  internal/HttpResponse.cpp
  internal/Logger.cpp
  internal/Request.cpp
  internal/XmlResponseParser.cpp
  internal/utils.cpp
)


set(fredcpp_external_SRCS)

if (WITH_CURL)
  set(fredcpp_external_SRCS
    ${fredcpp_external_SRCS}
    external/CurlHttpClient.cpp
  )
endif (WITH_CURL)


if (WITH_PUGIXML)
  set(fredcpp_external_SRCS
    ${fredcpp_external_SRCS}
    external/PugiXmlParser.cpp
    ${PUGIXML_SOURCE_DIR}/pugixml.cpp
  )
endif (WITH_PUGIXML)


if (WITH_SIMPLELOGGER)
  set(fredcpp_external_SRCS
    ${fredcpp_external_SRCS}
    external/SimpleLogger.cpp
  )
endif (WITH_SIMPLELOGGER)


include_directories(
  ${FREDCPP_PUBLIC_INCLUDE_DIRS}
  ${FREDCPP_PRIVATE_INCLUDE_DIRS}
)


add_library(${FREDCPP_STATIC_LIBRARY} STATIC
  ${fredcpp_SRCS}
  ${fredcpp_internal_SRCS}
  ${fredcpp_external_SRCS}
)

if (WITH_PUGIXML)
  add_dependencies(${FREDCPP_STATIC_LIBRARY} pugixml)
endif (WITH_PUGIXML)


if (MSVC)
  set(OUTPUT_SUFFIX static)
else (MSVC)
  set(OUTPUT_SUFFIX)
endif (MSVC)

set_target_properties(
  ${FREDCPP_STATIC_LIBRARY}
    PROPERTIES
      VERSION
        ${LIBRARY_VERSION}
      SOVERSION
        ${LIBRARY_SOVERSION}
      OUTPUT_NAME
        fredcpp
      ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_SUFFIX}
)

if (WIN32)
  set_target_properties(
    ${FREDCPP_STATIC_LIBRARY}
      PROPERTIES
        COMPILE_FLAGS
          "-DFREDCPP_STATIC"
  )
endif (WIN32)

install(
  TARGETS
    ${FREDCPP_STATIC_LIBRARY}
  DESTINATION
    ${INSTALL_LIB_DIR}/${OUTPUT_SUFFIX}
  COMPONENT
    libraries
)
