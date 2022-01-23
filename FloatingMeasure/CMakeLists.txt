cmake_minimum_required(VERSION 3.0.0)

# setting variables: 
# need compile commands for clazy analyzing the code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



# create list of all commonly used files
set(floatingmeasure_LIB
    Utils/Utils.h
    Utils/Utils.cpp
    Utils/Singleton.h
    Utils/CommonUtils.h
    Measure/VectorHandle.h
    Measure/VectorHandle.cpp
    Measure/PreMeasure.h
    Measure/PreMeasure.cpp
    Measure/BaseMeasure.h
    Measure/BaseMeasure.cpp
    Measure/SimpleMeasure.h
    Measure/SimpleMeasure.cpp
    Measure/MeasureOperator.cpp
    Measure/ComplexMeasure.cpp
    DigFloat/DigFloat.cpp
    FloatingMeasure/FloatingMeasure.cpp
)


#######################################
## add log4cplus support: enable
## compile switch LOG4CPLUS_ENABLED
######################################
#This module defines
#LOG4CPLUS_INCLUDE_DIRS, where to find tiff.h, etc.
#LOG4CPLUS_LIBRARIES, the libraries to link against to use log4cplus.

INCLUDE(FindPkgConfig)
######## comment in for log4cplus support #############
##FIND_PATH(LOG4CPLUS_INCLUDE_DIRS
##    NAMES logger.h
##    HINTS ${PC_LOG4CPLUS_INCLUDE_DIR}
##    ${CMAKE_INSTALL_PREFIX}/include
##    PATHS
##    C:\\Users\\AnyUser\\Source\\Repos\\log4cplus\\include
##
##)
##message("found log4cplus includes " ${LOG4CPLUS_INCLUDE_DIRS}) 
##include_directories(${LOG4CPLUS_INCLUDE_DIRS})
##
##FIND_LIBRARY(LOG4CPLUS_LIBRARIES
##    NAMES log4cplus
##    HINTS ${PC_LOG4CPLUS_LIBDIR}
##    C:\\Users\\AnyUser\\Source\\Repos\\log4cplus\\lib
##)
##
##message("found log4cplus libraries " ${LOG4CPLUS_LIBRARIES}) 
##
##
##
##INCLUDE(FindPackageHandleStandardArgs)
###FIND_PACKAGE_HANDLE_STANDARD_ARGS(CPPUNIT DEFAULT_MSG LOG4CPLUS_LIBRARIES LOG4CPLUS_INCLUDE_DIRS)
##MARK_AS_ADVANCED(LOG4CPLUS_LIBRARIES LOG4CPLUS_INCLUDE_DIRS)
##
##
###set version to be useable by calling script
##IF(LOG4CPLUS_INCLUDE_DIRS AND LOG4CPLUS_LIBRARIES)
##    
##    set(LOG4CPLUS_VERSION ${PC_LOG4CPLUS_VERSION} CACHE INTERNAL "log4cplus Version" FORCE)
##    add_compile_definitions(LOG4CPLUS_ENABLED)
##    # append to file list 
##    list(APPEND 
##        floatingmeasure_LIB       
##        Utils/LoggingStrings.h  
##        Utils/Log4cplusWrapper.h
##        Utils/Log4cplusWrapper.cpp
##    )
##
##    
##ELSE()
##    message(WARNING "Can't find include path for log4cplus: disabling logging" )
##ENDIF()

################# check log4cplus support END ##################

add_library(FloatingMeasure SHARED ${floatingmeasure_LIB})

# link against log4cplus
IF(LOG4CPLUS_INCLUDE_DIRS) 
 target_link_libraries(FloatingMeasure ${LOG4CPLUS_LIBRARIES})
ENDIF()


if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
	execute_process(
		COMMAND git rev-parse HEAD
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_BRANCH
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
else()
	set(GIT_BRANCH "Unknown")
endif()
add_definitions(-DGIT_BRANCH=${GIT_BRANCH})
message( STATUS "LIBRARY_OUTPUT_PATH: " ${LIBRARY_OUTPUT_PATH} )

#set build dir for your executable
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/CMake/lib)

#file(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})

#target_link_libraries( measurenum somename )

#If your app, links to an external lib -ie Boost
#target_link_libraries( measurenum ${Boost_LIBRARIES} )

# Install the executable and libraries (don't forget to uncomment the lib line if you want)
#install(TARGETS measurenum DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
#install(TARGETS FloatingMeasure DESTINATION ${CMAKE_INSTALL_PREFIX}/lib

# installation directory
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/build/CMake/)
install(TARGETS FloatingMeasure DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/FloatingMeasure/Utils DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/FloatingMeasure/FloatingMeasure DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/FloatingMeasure/Measure DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/FloatingMeasure/DigFloat DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING PATTERN "*.h")


# finally set the build type 
set(CMAKE_BUILD_TYPE Debug)
