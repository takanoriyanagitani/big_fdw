cmake_minimum_required(VERSION 3.0)

project(s1_fdw)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS_DEBUG   "-O0 -g -coverage")

add_compile_options(
  -mavx2
  -ftree-vectorize
  -Wall
  -Werror
)

add_library(s1_fdw SHARED s1_fdw.c)
set_property(TARGET s1_fdw PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET s1_fdw PROPERTY PREFIX "")
target_include_directories(s1_fdw PRIVATE
  /usr/include/postgresql/12/server
  ../common
)
