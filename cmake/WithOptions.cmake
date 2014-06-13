option(FREDCPP_BUILD_HTTP_CLIENT "Enable building of the supplied HTTP client." ON)
option(FREDCPP_BUILD_XML_PARSER "Enable building of the supplied XML parser." ON)
option(FREDCPP_BUILD_LOGGER "Enable building of the supplied logger facility." ON)
option(FREDCPP_BUILD_TESTS "Enable building of the unit and acceptance tests." ON)
option(FREDCPP_BUILD_EXAMPLES "Enable building of the examples." ON)

if (FREDCPP_BUILD_HTTP_CLIENT)
  option(FREDCPP_USE_CURL_HTTP
    "Build cURL-based HTTP client" ON
  )

  set(WITH_CURL ${FREDCPP_USE_CURL_HTTP})
endif (FREDCPP_BUILD_HTTP_CLIENT)

if (FREDCPP_BUILD_XML_PARSER)
  option(FREDCPP_USE_PUGIXML_PARSER
    "Enable building of pugixml-based XML parser." ON
  )

  set(WITH_PUGIXML ${FREDCPP_USE_PUGIXML_PARSER})
endif (FREDCPP_BUILD_XML_PARSER)

if (FREDCPP_BUILD_LOGGER)
  option(FREDCPP_USE_SIMPLELOGGER
    "Enable building of SimpleLogger-based logger facility." ON
  )

  set(WITH_SIMPLELOGGER ${FREDCPP_USE_SIMPLELOGGER})
endif (FREDCPP_BUILD_LOGGER)

if (FREDCPP_BUILD_TESTS)
  set(WITH_TESTS ${FREDCPP_BUILD_TESTS})
endif (FREDCPP_BUILD_TESTS)

if (FREDCPP_BUILD_EXAMPLES)
  set(WITH_EXAMPLES ${FREDCPP_BUILD_EXAMPLES})
endif (FREDCPP_BUILD_EXAMPLES)
