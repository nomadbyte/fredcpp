project(gtest)

set(gtest_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}
  CACHE INTERNAL "gtest dir"
)

set(GTEST_SOURCE_DIR
  ${gtest_DIR}/fused-src/gtest
  CACHE INTERNAL "gtest source dir"
)

set(GTEST_INCLUDE_DIRS
  ${gtest_DIR}/fused-src
  CACHE INTERNAL "gtest include dirs"
)


include_directories(
  ${GTEST_INCLUDE_DIRS}
)


add_library(gtest STATIC ${GTEST_SOURCE_DIR}/gtest-all.cc)

add_library(gtest_main STATIC ${GTEST_SOURCE_DIR}/gtest_main.cc)


if (UNIX)
  find_package(Threads REQUIRED)

  set(GTEST_LINK_LIBRARIES
    gtest
    gtest_main
    ${CMAKE_THREAD_LIBS_INIT}
    CACHE INTERNAL "gtest libraries"
  )

else (UNIX)
  set(GTEST_LINK_LIBRARIES
    gtest
    gtest_main
    CACHE INTERNAL "gtest libraries"
  )
endif (UNIX)

