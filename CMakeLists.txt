# Modify By yourself!
project(Project)
cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

# Configurations
include(configure.cmake)
include(amsdk-cmake/Initialize.cmake)
add_subdirectory(src)