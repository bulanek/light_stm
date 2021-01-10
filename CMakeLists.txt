# ==============================================================================
# README
# ==============================================================================
# Usage: cmake -G<Type of Makefile> -DCMAKE_TOOLCHAIN_PATH=<PATH> [path to this file]
#			-DCMAKE_BUILD_TYPE={Debug,Release}
# Note: Build folder should be outside of this directory (pnio_src) as test 
# sources are used for arm-gcc toolchain, which would be added 
# to compilation process (handled all of sources inside this directory)
#
# Default type of build is Release.
#
#	External vars:  None
# ------------------------------------------------------------------------------
# CMAKE PROJECT PROPERTIES
# ------------------------------------------------------------------------------

# CMake version
cmake_minimum_required( VERSION 3.6 )  # FILTER in list

# Project name
set(DOXYGEN_PROJECT_NUMBER "LIGHT_CTRL_0.1.1")
project( LIGHT
VERSION 0.1.1  
LANGUAGES C CXX ASM
)

# Build type
if (NOT CMAKE_BUILD_TYPE)
	set( CMAKE_BUILD_TYPE "Debug" CACHE INTERNAL "Build type")
	message(STATUS "Build in default Debug mode")
endif()


# Output verbosity (default is OFF)
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set( CMAKE_VERBOSE_MAKEFILE "OFF" )
endif()

# Binary file name
set(APP_BIN_NAME light_ctrl CACHE STRING "Name of application bin file")

if(${TARGET_TYPE} STREQUAL "STM8")
include ("CMakeListsSTM8.cmake")
elseif(${TARGET_TYPE} STREQUAL "STM32")
include ("CMakeListsSTM32.cmake")
else()
message(FATAL_ERROR "Unexpected target ${TARGET_TYPE}")
endif()


# ------------------------------------------------------------------------------
# SOURCES
# ------------------------------------------------------------------------------

# list all et(SOURCES)
foreach(module src _cfg  )
	file(GLOB_RECURSE TMP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${module}/*.c*)
	list(APPEND SOURCES ${TMP_SOURCES})
endforeach(module)


# ------------------------------------------------------------------------------
# INCLUDES
# ------------------------------------------------------------------------------
SET (INC_DIRS ${INC_DIRS}
	${COMPILER_INC_DIR} # gcc includes
  	${CMAKE_CURRENT_SOURCE_DIR}/inc
  	${CMAKE_CURRENT_SOURCE_DIR}/_cfg
    ${CMAKE_CURRENT_SOURCE_DIR}/src/_com
    )

include_directories(${INC_DIRS})

# ------------------------------------------------------------------------------
# BUILD
# ------------------------------------------------------------------------------


set(CMAKE_EXECUTABLE_SUFFIX ".exe")          # intel hex file .ihx -> .exe bug
add_executable(${PROJECT_NAME} ${SOURCES} )

target_link_libraries(${PROJECT_NAME} ${TARGET_LINK_LIBRARIES})

#add_custom_command(
#		TARGET ${PROJECT_NAME} 
#		POST_BUILD
#		COMMAND  cmake -E copy ${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX} ${PROJECT_NAME}.ihx # intel hex file .ihx -> .exe bug
#		COMMENT "Creation of ${PROJECT_NAME}"
#		)

add_custom_command(
		TARGET ${PROJECT_NAME} 
		POST_BUILD
		COMMAND  cmake.exe -E copy ${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX} ${PROJECT_NAME}
		COMMENT "Creation of ${PROJECT_NAME}"
		)

# CMAKE_OBJCOPY defined in the Toolchain.
add_custom_command(
		TARGET ${PROJECT_NAME} 
		POST_BUILD
		COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME} ${APP_BIN_NAME}.bin
		COMMENT "Creation of ${APP_BIN_NAME}.bin "
		)




# ------------------------------------------------------------------------------
# DOC 
# ------------------------------------------------------------------------------

find_package(Doxygen)
message(STATUS "Doxygen version: ${DOXYGEN_VERSION}")

set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_LATEX NO)
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_INSTALL_PREFIX}/doc")
set(DOXYGEN_FILE_PATTERNS "*.c;*.cc;*.cpp;*.h;*.hpp")

# The RECURSIVE tag can be used to specify whether or not subdirectories should
# be searched for input files as well.
# The default value is: NO.
set(DOXYGEN_RECURSIVE YES)
##If the ENABLE_PREPROCESSING tag is set to YES, doxygen will evaluate all C-preprocessor directives found in the sources and include files
set(DOXYGEN_ENABLE_PREPROCESSING NO)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

set(DOX_INPUT ) 
# Only public interface doc for release.
set(DOX_INPUT ${CMAKE_CURRENT_SOURCE_DIR})
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(DOXYGEN_EXTRACT_PRIVATE YES)
endif()

# Function from Doxygen package. It generates doxygen config file using DOXYGEN_<doxygen_var> variables
doxygen_add_docs(
        recorder_doc                                                 # custom target doc
        ${DOX_INPUT}
        COMMENT    "Generate man pages" 
)

# ------------------------------------------------------------------------------
# INSTALL
# ------------------------------------------------------------------------------
install(
	TARGETS ${PROJECT_NAME} 
    RUNTIME	DESTINATION	${CMAKE_INSTALL_PREFIX}
)
# Files created by add_custom_command (objcopy,..)
install(FILES 			${CMAKE_CURRENT_BINARY_DIR}/${APP_BIN_NAME}.bin 
						${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map  
		DESTINATION 	${CMAKE_INSTALL_PREFIX}
)
