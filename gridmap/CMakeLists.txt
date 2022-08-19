add_library(gridmap
  circle.h
  grid.h
  grid.cc
  gridmap.h
  gridmap.cc
)

# target_link_libraries(gridmap PRIVATE raylib)
target_include_directories(gridmap PRIVATE ${MIHOYO_TEST_ROOT})