cmake_minimum_required(VERSION 3.0.0)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_BUILD_DIR ${PROJECT_SOURCE_DIR}/build)

# add subdirs 
add_subdirectory(src/)
add_subdirectory(Test/)
