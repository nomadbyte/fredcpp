# FRED API key is needed for acceptance testing.
# By default the key value is expected in api.key text file

set(FREDCPP_API_KEY_FILE "${CMAKE_SOURCE_DIR}/api.key"
  CACHE FILEPATH "FRED API key file"
)

if (NOT EXISTS "${FREDCPP_API_KEY_FILE}")
  message(SEND_ERROR "FRED API key is needed for acceptance testing: '${FREDCPP_API_KEY_FILE}'")
endif (NOT EXISTS "${FREDCPP_API_KEY_FILE}")

