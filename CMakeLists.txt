cmake_minimum_required(VERSION 3.0.0)

project(FloatingMeasure
        VERSION 1.0.0.1
        LANGUAGES CXX)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_BUILD_DIR ${PROJECT_SOURCE_DIR}/build)

# add subdirs 
add_subdirectory(FloatingMeasure/)
add_subdirectory(FloatingMeasure_Test/)
add_subdirectory(FloatingMeasure_Examples/)

# compiler flags
set(CMAKE_CXX_FLAGS "-std=c++14 -pedantic")

