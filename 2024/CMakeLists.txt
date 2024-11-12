cmake_minimum_required(VERSION 3.29)

project(aoc2024 CXX C ASM)

set(CMAKE_TOOLCHAIN_FILE "A:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain")


# Must be set before including CTest so that these arguments are applied when
# running `$ ninja test` or `$ make test`.
set(CMAKE_CTEST_ARGUMENTS "--output-on-failure" "--output-junit" "junit.xml")
# This must be in the top-level CMakeLists.txt to enable CMake/CTest support.
include(CTest)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src/lib/foo)
add_subdirectory(src/lib/example)


if(BUILD_TESTING)
  add_subdirectory(src/tests)
endif()
