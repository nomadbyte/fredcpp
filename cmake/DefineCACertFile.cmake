# CACert file is needed for acceptance testing.
# By default the key value is expected in cacert.pem text file
# The CA certificate bundle can be dowloaded from cURL site:
#   http://curl.haxx.se/docs/caextract.html

set(FREDCPP_CACERT_FILE "${CMAKE_SOURCE_DIR}/cacert.pem"
  CACHE FILEPATH "FRED CACert file"
)

if (NOT EXISTS "${FREDCPP_CACERT_FILE}")
  message(SEND_ERROR "FRED CACert file is needed for acceptance testing: '${FREDCPP_CACERT_FILE}'."
                     "CACert bundle can be downloaded from http://curl.haxx.se/docs/caextract.html")
endif (NOT EXISTS "${FREDCPP_CACERT_FILE}")

