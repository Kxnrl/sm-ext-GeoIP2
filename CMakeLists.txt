# Modify By yourself!
project(GeoIP2)
cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

# Configurations
include(configure.cmake)
include(amsdk-cmake/Initialize.cmake)

if (NOT WIN32)
    if (TARGET_ARCH MATCHES "x86")
        add_definitions(-DMMDB_UINT128_IS_BYTE_ARRAY=1)
    endif()
endif()

add_subdirectory(src)