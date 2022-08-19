cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(mihoyo)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
set(MIHOYO_TEST_ROOT ${PROJECT_SOURCE_DIR})
include_directories(${MIHOYO_TEST_ROOT})

# Dependencies
find_package(raylib 4.2.0 QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

add_subdirectory(math)
add_subdirectory(gridmap)

# Our Project
add_executable(${PROJECT_NAME} core_basic_window.c)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib gridmap)
target_include_directories(${PROJECT_NAME} PRIVATE ${MIHOYO_TEST_ROOT})

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

add_executable(test_node tutorial.cc)
target_link_libraries(test_node raylib gridmap mihoyo_math)