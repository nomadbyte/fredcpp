
## Read install manifest file and remove each previously installed file
## NOTE: Removes only files, so directories may be left empty
##
## Used as a handler for uninstall target:
## add_custom_target(uninstall
##    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/cmake/CMakeUninstall.cmake
## )

set(INSTALL_MANIFEST "${CMAKE_BINARY_DIR}/install_manifest.txt")

if(NOT EXISTS ${INSTALL_MANIFEST})
  message(FATAL_ERROR "Cannot find install manifest: ${INSTALL_MANIFEST}")
endif(NOT EXISTS ${INSTALL_MANIFEST})

file(READ ${INSTALL_MANIFEST} files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach(file ${files})
  message(STATUS "Uninstalling $ENV{DESTDIR}${file}")

  if(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    exec_program(
      "${CMAKE_COMMAND}" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
    )
    if(NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing $ENV{DESTDIR}${file}")
    endif(NOT "${rm_retval}" STREQUAL 0)

  else(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    message(STATUS "File $ENV{DESTDIR}${file} does not exist.")

  endif(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")

endforeach(file)
