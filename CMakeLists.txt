cmake_minimum_required (VERSION 2.8.11)

project (TestTaskTree)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  set(CMAKE_CXX_FLAGS         "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
  set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

add_subdirectory (External)
add_subdirectory (Tests)
add_subdirectory (Tree)
