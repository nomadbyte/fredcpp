project(pugixml)

set(pugixml_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}
  CACHE INTERNAL "pugixml dir"
)


set(PUGIXML_SOURCE_DIR
  ${pugixml_DIR}/src
  CACHE INTERNAL "pugixml source dir"
)  

set(PUGIXML_INCLUDE_DIRS
  ${pugixml_DIR}/src
  CACHE INTERNAL "pugixml include dirs"
)

