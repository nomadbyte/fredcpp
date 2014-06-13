IF (NOT APPLICATION_NAME)
  MESSAGE(STATUS "${PROJECT_NAME} is used as APPLICATION_NAME")
  SET(APPLICATION_NAME ${PROJECT_NAME})
ENDIF (NOT APPLICATION_NAME)

# Suffix to denote 32/64-bit 
SET(PLATFORM_BIT_SUFFIX
  CACHE STRING "Define suffix for platform-specific directory names (32/64)"
)


IF (UNIX OR OS2)
  SET(INSTALL_EXEC_PREFIX
    "${CMAKE_INSTALL_PREFIX}"
    CACHE INTERNAL  "Base directory for executables and libraries"
  )
  SET(INSTALL_SHARE_PREFIX
    "${CMAKE_INSTALL_PREFIX}/share"
    CACHE INTERNAL "Base directory for files which go to share/"
  )
  SET(INSTALL_DATA_PREFIX
    "${INSTALL_SHARE_PREFIX}/${APPLICATION_NAME}"
    CACHE INTERNAL "The parent directory where applications can install their data")

  # The following are directories where stuff will be installed to
  SET(INSTALL_BIN_DIR
    "${INSTALL_EXEC_PREFIX}/bin"
    CACHE INTERNAL "The ${APPLICATION_NAME} binary install dir (default prefix/bin)"
  )
  SET(INSTALL_SBIN_DIR
    "${INSTALL_EXEC_PREFIX}/sbin"
    CACHE INTERNAL "The ${APPLICATION_NAME} sbin install dir (default prefix/sbin)"
  )
  SET(INSTALL_LIB_DIR
    "${INSTALL_EXEC_PREFIX}/lib${PLATFORM_BIT_SUFFIX}"
    CACHE INTERNAL "The subdirectory relative to the install prefix where libraries will be installed (default is prefix/lib)"
  )
  SET(INSTALL_LIBEXEC_DIR
    "${INSTALL_EXEC_PREFIX}/libexec"
    CACHE INTERNAL "The subdirectory relative to the install prefix where libraries will be installed (default is prefix/libexec)"
  )
  SET(INSTALL_PLUGIN_DIR
    "${INSTALL_LIB_DIR}/${APPLICATION_NAME}"
    CACHE INTERNAL "The subdirectory relative to the install prefix where plugins will be installed (default is prefix/lib/${APPLICATION_NAME})"
  )
  SET(INSTALL_INCLUDE_DIR
    "${CMAKE_INSTALL_PREFIX}/include"
    CACHE INTERNAL "The subdirectory to the header prefix (default prefix/include)"
  )

  set(INSTALL_CMAKE_DIR
    "${INSTALL_LIB_DIR}/cmake"
    CACHE INTERNAL "The subdirectory to install cmake config files")

  SET(INSTALL_DATA_DIR
    "${INSTALL_DATA_PREFIX}"
    CACHE INTERNAL "The parent directory where applications can install their data (default prefix/share/${APPLICATION_NAME})"
  )
  SET(INSTALL_DOC_HTML_DIR
    "${INSTALL_DATA_PREFIX}/doc/html"
    CACHE INTERNAL "The HTML install dir for documentation (default data/doc/html)"
  )
  SET(INSTALL_ICONS_DIR
    "${INSTALL_DATA_PREFIX}/icons"
    CACHE INTERNAL "The icon install dir (default data/icons/)"
  )
  SET(INSTALL_SOUNDS_DIR
    "${INSTALL_DATA_PREFIX}/sounds"
    CACHE INTERNAL "The install dir for sound files (default data/sounds)"
  )

  SET(INSTALL_LOCALE_DIR
    "${INSTALL_SHARE_PREFIX}/locale"
    CACHE INTERNAL "The install dir for translations (default prefix/share/locale)"
  )

  SET(XDG_APPS_DIR
    "${INSTALL_SHARE_PREFIX}/applications/"
    CACHE INTERNAL "The XDG apps dir"
  )
  SET(XDG_DIRECTORY_DIR
    "${INSTALL_SHARE_PREFIX}/desktop-directories"
    CACHE INTERNAL "The XDG directory"
  )

  SET(INSTALL_SYSCONF_DIR
    "${INSTALL_EXEC_PREFIX}/etc"
    CACHE INTERNAL "The ${APPLICATION_NAME} sysconfig install dir (default prefix/etc)"
  )
  SET(INSTALL_MAN_DIR
    "${INSTALL_SHARE_PREFIX}/man"
    CACHE INTERNAL "The ${APPLICATION_NAME} man install dir (default prefix/man)"
  )
  SET(INSTALL_INFO_DIR
    "${INSTALL_SHARE_PREFIX}/info"
    CACHE INTERNAL "The ${APPLICATION_NAME} info install dir (default prefix/info)"
  )

ELSE (UNIX OR OS2)
  # Same same
  set(INSTALL_BIN_DIR "bin" CACHE INTERNAL "-")
  set(INSTALL_SBIN_DIR "sbin" CACHE INTERNAL "-")
  set(INSTALL_LIB_DIR "lib${PLATFORM_BIT_SUFFIX}" CACHE INTERNAL "-")
  set(INSTALL_INCLUDE_DIR "include" CACHE INTERNAL "-")
  set(INSTALL_CMAKE_DIR "CMake" CACHE INTERNAL "-")
  set(INSTALL_PLUGIN_DIR "plugins" CACHE INTERNAL "-")
  set(INSTALL_DOC_HTML_DIR "doc/html" CACHE INTERNAL "-")
  set(INSTALL_ICONS_DIR "icons" CACHE INTERNAL "-")
  set(INSTALL_SOUNDS_DIR "sounds" CACHE INTERNAL "-")
  set(INSTALL_LOCALE_DIR "lang" CACHE INTERNAL "-")
ENDIF (UNIX OR OS2)
