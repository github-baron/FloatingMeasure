cmake_minimum_required(VERSION 3.10)

#set the project name
project(FMEx_Velocity)
add_executable(FMEx_Velocity FMEx_Velocity.cpp)
add_executable(FMEx_CheckMeasValue FMEx_CheckMeasValue.cpp)


include_directories(../FloatingMeasure/ )


target_include_directories(FMEx_Velocity PRIVATE ${CMAKE_INSTALL_PREFIX}/include)
link_directories(FMEx_Velocity PRIVATE ${CMAKE_INSTALL_PREFIX}/lib)

FIND_LIBRARY(FM_LIBRARIES
    NAMES FloatingMeasure 
    HINTS ${PROJECT_SOURCE_DIR}../build
    ${CMAKE_INSTALL_PREFIX}/lib
    ${CMAKE_INSTALL_PREFIX}/lib64
    PATHS
    ${CPPUNIT_INCLUDE_DIRS}/../lib
    /usr/local/lib
    /usr/lib
    /usr/lib/x86_64-linux-gnu/
    ${PROJECT_SOURCE_DIR}../FloatingMeasure/
)


# link cppunit and FloatingMeasure lib
target_link_libraries(FMEx_Velocity FloatingMeasure)
target_link_libraries(FMEx_CheckMeasValue FloatingMeasure)

#install into cmake / bin
# installation directory
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../build/CMake/)
install(TARGETS FMEx_Velocity FMEx_CheckMeasValue RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
