cmake_minimum_required(VERSION 3.12)
project(CsvQuery CXX)

set(CMAKE_CXX_STANDARD 17)
option(BUILD_CCACHE "Whether to enable ccache" ON)
if(BUILD_CCACHE)
  set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif()
