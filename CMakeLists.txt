cmake_minimum_required(VERSION 3.1)

project(PixelEngine CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

if (${BUILD_TYPE} STREQUAL "coverage")
  
  set(CMAKE_BUILD_TYPE DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")

elseif (${BUILD_TYPE} STREQUAL "debug")

  set(CMAKE_BUILD_TYPE DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

elseif (${BUILD_TYPE} STREQUAL "release")
  
  set(CMAKE_BUILD_TYPE RELEASE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O6")

endif()

add_subdirectory(src)

