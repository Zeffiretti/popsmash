#!/bin/bash

### Usage: ./build_linux.sh config [build-tool]
###
### config:
###   debug   -   build with the debug configuration
###   release -   build with the release configuration
###
### build-tool:
###   make    -   build with Unix Make (default)
###   ninja   -   build with Ninja

set -ex
help() {
  sed -rn 's/^### ?//;T;p' "$0"
}

parseconfig(){
  if test \( \( -n "$1" \) -a \( "$1" = "debug" \) \);then
    CMAKE_ARG_BUILD_TYPE_CONFIG="-DCMAKE_BUILD_TYPE=Debug"
  elif test \( \( -n "$1" \) -a \( "$1" = "release" \) \);then
    CMAKE_ARG_BUILD_TYPE_CONFIG="-DCMAKE_BUILD_TYPE=Release"
  else
    echo "The config \"$1\" is not supported!"
    echo ""
    echo "Configs:"
    echo "  debug   -   build with the debug configuration"
    echo "  release -   build with the release configuration"
    echo ""
    exit 1
  fi
}

if [[ "$1" == "-h" ]] || [[ "$1" == "--help" ]]; then
  help
  exit 1
fi

if test \( $# -eq 0 \); then
  CMAKE_ARG_BUILD_TOOL_TYPE_CONFIG="Unix Makefiles"
  CMAKE_ARG_BUILD_TYPE_CONFIG="-DCMAKE_BUILD_TYPE=Release"
elif test \( $# -eq 1 \) ;then
  if command -v make &> /dev/null; then
    CMAKE_ARG_BUILD_TOOL_TYPE_CONFIG="Unix Makefiles"
  else
    CMAKE_ARG_BUILD_TOOL_TYPE_CONFIG="Ninja"
  fi
  parseconfig $1
elif test \( \( -n "$2" \) -a \( "$2" = "make" \) \);then
  CMAKE_ARG_BUILD_TOOL_TYPE_CONFIG="Unix Makefiles"
  parseconfig $1
elif test \( \( -n "$2" \) -a \( "$2" = "ninja" \) \);then
  CMAKE_ARG_BUILD_TOOL_TYPE_CONFIG="Ninja"
  parseconfig $1
else
  echo "The build-tool \"$2\" is not supported!"
  exit 1
fi

MY_DIR="$(cd "$(dirname "$0")/.." 1>/dev/null 2>/dev/null && pwd)"
cd "${MY_DIR}"
if [[ ! -d build ]]; then
  mkdir build
fi

cmake -S . -B build "${CMAKE_ARG_BUILD_TYPE_CONFIG}" -G "${CMAKE_ARG_BUILD_TOOL_TYPE_CONFIG}" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "${MY_DIR}/build" -- all -j$(nproc)
