add_library(gridmap STATIC
  circle.h
  line.h
  line.cc
  gridmap.h
  gridmap.cc
  quadtree.h
  quadtree.cc
)

target_link_libraries(gridmap PRIVATE raylib mihoyo_math)
target_include_directories(gridmap PRIVATE ${MIHOYO_TEST_ROOT})
message("MOHOYO_TEST_ROOT: ${MIHOYO_TEST_ROOT}")