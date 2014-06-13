
set(fredcpp_FACILITY "fredcpp"
  CACHE INTERNAL "fredcpp facility name"
)

set(fredcpp_BRIEF "FRED API client for C++"
  CACHE INTERNAL "${fredcpp_FACILITY} facility description"
)

set(fredcpp_VERSION_MAJOR 0
  CACHE INTERNAL "${fredcpp_FACILITY} major release version"
)

set(fredcpp_VERSION_MINOR 6
  CACHE INTERNAL "${fredcpp_FACILITY} minor release version"
)

set(fredcpp_VERSION_PATCH 0
  CACHE INTERNAL "${fredcpp_FACILITY} patch release version"
)

set(fredcpp_VERSION_STRING "${fredcpp_VERSION_MAJOR}.${fredcpp_VERSION_MINOR}.${fredcpp_VERSION_PATCH}"
  CACHE INTERNAL "${fredcpp_FACILITY} release version string"
)
