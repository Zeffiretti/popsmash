add_library(gridmap STATIC
  circle.h
  line.h
  line.cc
  grid.h
  grid.cc
  gridmap.h
  gridmap.cc
)

target_link_libraries(gridmap PRIVATE raylib)
target_include_directories(gridmap PRIVATE ${MIHOYO_TEST_ROOT})
message("MOHOYO_TEST_ROOT: ${MIHOYO_TEST_ROOT}")