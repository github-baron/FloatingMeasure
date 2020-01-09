cmake_minimum_required(VERSION 3.10)

#set the project name
project(Measure_test)

#add the executable
#http://www.cmake.org/pipermail/cmake/2006-October/011446.html
#Modified to use pkg config and use standard var names
add_executable(TestRunner TestRunner.cpp)

include_directories(../src/)
##target_link_libraries(TestRunner ${CMAKE_BUILD_DIR}/lib/MeasureNum.so)


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
    /usr/include
)
message("found cppunit includes " ${CPPUNIT_INCLUDE_DIRS}) 

FIND_LIBRARY(CPPUNIT_LIBRARIES
    NAMES cppunit 
    HINTS ${PC_CPPUNIT_LIBDIR}
    ${CMAKE_INSTALL_PREFIX}/lib
    ${CMAKE_INSTALL_PREFIX}/lib64
    PATHS
    ${CPPUNIT_INCLUDE_DIRS}/../lib
    /usr/local/lib
    /usr/lib
    /usr/lib/x86_64-linux-gnu/
)

message("found cppunit libraries " ${CPPUNIT_LIBRARIES}) 

INCLUDE(FindPackageHandleStandardArgs)
#FIND_PACKAGE_HANDLE_STANDARD_ARGS(CPPUNIT DEFAULT_MSG CPPUNIT_LIBRARIES CPPUNIT_INCLUDE_DIRS)
MARK_AS_ADVANCED(CPPUNIT_LIBRARIES CPPUNIT_INCLUDE_DIRS)


#set version to be useable by calling script

IF(CPPUNIT_FOUND)
    set(CPPUNIT_VERSION ${PC_CPPUNIT_VERSION} CACHE INTERNAL "CppUnit Version" FORCE)
ENDIF()



target_link_libraries(TestRunner ${CPPUNIT_LIBRARIES} FloatingMeasure)
