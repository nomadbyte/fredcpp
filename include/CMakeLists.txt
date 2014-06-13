project(headers)

## generate config
##
configure_file(config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)

add_subdirectory(fredcpp)
