project(mihoyo_math)

add_library(mihoyo_math STATIC 
  geometry.h
  geometry.cc
)
target_include_directories(mihoyo_math PRIVATE ${MIHOYO_TEST_ROOT})
target_link_libraries(mihoyo_math PRIVATE gridmap raylib)