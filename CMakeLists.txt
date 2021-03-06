cmake_minimum_required(VERSION 3.12)
project(CsvQuery CXX)

set(CMAKE_CXX_STANDARD 20)
option(BUILD_CCACHE "Whether to enable ccache" ON)
if(BUILD_CCACHE)
  set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif()

add_library(
  CsvQueryLib STATIC
  select.cc
  take.cc
  order_by.cc
  join.cc
  count_by.cc
  from.cc
  fstream_fs.cc
  query.cc
  real_fs.cc
  real_operator_factory.cc)

add_subdirectory(vendor/range-v3)
target_link_libraries(CsvQueryLib range-v3)

add_executable(CsvQuery main.cc)
target_link_libraries(CsvQuery CsvQueryLib)

set(INSTALL_GTEST
    OFF
    CACHE BOOL "")
add_subdirectory(vendor/googletest EXCLUDE_FROM_ALL)

add_executable(
  csv-query-test
  select_test.cc
  fake_record_set.cc
  take_test.cc
  order_by_test.cc
  join_test.cc
  count_by_test.cc
  from_test.cc
  fake_fs.cc
  fs_provider_test.cc
  query_test.cc)

target_link_libraries(csv-query-test CsvQueryLib gmock_main)

include(GoogleTest)
enable_testing()
gtest_discover_tests(csv-query-test)
