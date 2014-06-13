project(fredcpp-headers)

## generate version.h
##
set(fredcpp_version_h ${CMAKE_CURRENT_BINARY_DIR}/version.h)

configure_file(version.h.cmake ${fredcpp_version_h})


set(fredcpp_HDRS
  Api.h
  ApiError.h
  ApiLog.h
  ApiRequest.h
  ApiRequestBuilder.h
  ApiResponse.h
  fredcpp.h
  fredcppdefs.h
  FredCategoryRequest.h
  FredEntityRequest.h
  FredReleaseRequest.h
  FredSeriesRequest.h
  FredSourceRequest.h
  ${fredcpp_version_h}
)

set(fredcpp_internal_HDRS
  internal/HttpRequest.h
  internal/HttpRequestExecutor.h
  internal/HttpResponse.h
  internal/Logger.h
  internal/Request.h
  internal/XmlResponseParser.h
  internal/utils.h
)


set(fredcpp_external_HDRS)

if (WITH_CURL)
  set(fredcpp_external_HDRS
    ${fredcpp_external_HDRS}
    external/CurlHttpClient.h
  )
endif (WITH_CURL)


set(fredcpp_third_party_DIR ${CMAKE_CURRENT_BINARY_DIR}/third_party)

if (WITH_PUGIXML)
  ## integrate pugixml headers into build-tree
  add_custom_target(pugixml ALL
    DEPENDS ${fredcpp_third_party_DIR}/pugixml
  )

  add_custom_command(OUTPUT ${fredcpp_third_party_DIR}/pugixml
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
      ${PUGIXML_SOURCE_DIR} ${fredcpp_third_party_DIR}/pugixml
    DEPENDS ${PUGIXML_SOURCE_DIR}
  )

  set(fredcpp_external_HDRS
    ${fredcpp_external_HDRS}
    external/PugiXmlParser.h
  )
endif (WITH_PUGIXML)

if (WITH_SIMPLELOGGER)
  set(fredcpp_external_HDRS
    ${fredcpp_external_HDRS}
    external/SimpleLogger.h
  )
endif (WITH_SIMPLELOGGER)


## install
##
install(
  FILES
    ${fredcpp_HDRS}
  DESTINATION
    ${INSTALL_INCLUDE_DIR}/${APPLICATION_NAME}
  COMPONENT
    headers
)

install(
  FILES
    ${fredcpp_internal_HDRS}
  DESTINATION
    ${INSTALL_INCLUDE_DIR}/${APPLICATION_NAME}/internal
  COMPONENT
    headers
)

if (fredcpp_external_HDRS)
  install(
    FILES
      ${fredcpp_external_HDRS}
    DESTINATION
      ${INSTALL_INCLUDE_DIR}/${APPLICATION_NAME}/external
    COMPONENT
      headers
  )
endif (fredcpp_external_HDRS)


if (fredcpp_third_party_DIR)
  # install only headers
  install(
    DIRECTORY
      ${fredcpp_third_party_DIR}
    DESTINATION
      ${INSTALL_INCLUDE_DIR}/${APPLICATION_NAME}
    COMPONENT
      "third-party-headers"
    FILES_MATCHING REGEX "\\.(h|hpp|hxx)$"
  )
endif (fredcpp_third_party_DIR)
