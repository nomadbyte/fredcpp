project(fredcpp-third_party)

if (WITH_PUGIXML)
  add_subdirectory(pugixml-1.2)
endif (WITH_PUGIXML)

if (WITH_TESTS)
  add_subdirectory(gtest-1.6.0)
endif (WITH_TESTS)
