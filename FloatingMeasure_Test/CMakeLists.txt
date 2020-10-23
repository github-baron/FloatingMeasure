cmake_minimum_required(VERSION 3.10)

#set the project name
project(FloatingMeasure_Test)

#add the executable
#http://www.cmake.org/pipermail/cmake/2006-October/011446.html
#Modified to use pkg config and use standard var names
add_executable(FloatingMeasure_Test FloatingMeasure_TestRunner.cpp)


#Find the CppUnit includes and library

#This module defines
#CPPUNIT_INCLUDE_DIR, where to find tiff.h, etc.
#CPPUNIT_LIBRARIES, the libraries to link against to use CppUnit.
#CPPUNIT_FOUND, If false, do not try to use CppUnit.

INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_CPPUNIT "cppunit")

FIND_PATH(CPPUNIT_INCLUDE_DIRS
    NAMES cppunit/TestCase.h
    HINTS ${PC_CPPUNIT_INCLUDE_DIR}
    ${CMAKE_INSTALL_PREFIX}/include
    PATHS
    /usr/local/include
    /usr/include/
    C:\\Users\\Michae\\Source\\Repos\\Ultimaker\\CppUnit\\src\\cppunit\\include

)
message("found cppunit includes " ${CPPUNIT_INCLUDE_DIRS}) 
include_directories(../FloatingMeasure/ ${CPPUNIT_INCLUDE_DIRS})

FIND_LIBRARY(CPPUNIT_LIBRARIES
    NAMES cppunit
    HINTS ${PC_CPPUNIT_LIBDIR}
#    ${CMAKE_INSTALL_PREFIX}/lib
#    ${CMAKE_INSTALL_PREFIX}/lib64
#    PATHS
#    ${CPPUNIT_INCLUDE_DIRS}/../lib
    /usr/local/lib
    /usr/lib
    /usr/lib/x86_64-linux-gnu/
    C:\\Users\\Michae\\Source\\Repos\\Ultimaker\\CppUnit\\src\\cppunit\\lib
)

message("found cppunit libraries " ${CPPUNIT_LIBRARIES}) 

INCLUDE(FindPackageHandleStandardArgs)
#FIND_PACKAGE_HANDLE_STANDARD_ARGS(CPPUNIT DEFAULT_MSG CPPUNIT_LIBRARIES CPPUNIT_INCLUDE_DIRS)
MARK_AS_ADVANCED(CPPUNIT_LIBRARIES CPPUNIT_INCLUDE_DIRS)


#set version to be useable by calling script

IF(CPPUNIT_FOUND)
    set(CPPUNIT_VERSION ${PC_CPPUNIT_VERSION} CACHE INTERNAL "CppUnit Version" FORCE)
ENDIF()

# link cppunit and FloatingMeasure lib
target_link_libraries(FloatingMeasure_Test ${CPPUNIT_LIBRARIES} FloatingMeasure)

#install into cmake / bin
# installation directory
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../build/CMake/)
install(TARGETS FloatingMeasure_Test RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
