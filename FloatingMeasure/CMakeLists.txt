cmake_minimum_required(VERSION 3.0.0)

# setting variables: 
# need compile commands for clazy analyzing the code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#Rename the source files that will create the library, to a proper name!
set(floatingmeasure_LIB
    Utils/Utils.h
    Utils/Utils.cpp
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
add_library(FloatingMeasure SHARED ${floatingmeasure_LIB})

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