cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(mihoyo)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
set(MIHOYO_TEST_ROOT ${PROJECT_SOURCE_DIR})
include_directories(${MIHOYO_TEST_ROOT})

# Dependencies
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
add_subdirectory(3rdparty/raylib)
add_subdirectory(math)
add_subdirectory(gridmap)

# Our Project
add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} gridmap)
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
