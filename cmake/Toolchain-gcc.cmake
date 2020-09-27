
# Targeting an embedded system, no OS.
set(CMAKE_SYSTEM_NAME Generic)

#Not used, only for possibility of further usage in projects
set(CMAKE_SYSTEM_PROCESSOR arm)

if (WIN32)
	set(COMPILER_HOME "C:/git/mf_dev/Tools/gnu_tools_arm_embedded_9_2019_q4_major")
	set(TOOL_EXECUTABLE_SUFFIX ".exe")
endif()


get_filename_component(ARM_GCC_HOME ${COMPILER_HOME} ABSOLUTE)
set(ARM_GCC_PREFIX arm-none-eabi)
set(ARM_GCC_BIN_DIR ${ARM_GCC_HOME}/bin )
set(COMPILER_INC_DIR ${ARM_GCC_HOME}/arm-none-eabi/include)
set(COMPILER_LIB_DIR ${ARM_GCC_HOME}/arm-none-eabi/lib)

SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

SET(CMAKE_C_COMPILER ${ARM_GCC_BIN_DIR}/arm-none-eabi-gcc${TOOL_EXECUTABLE_SUFFIX}  )#CACHE INTERNAL "C compiler")
SET(CMAKE_CXX_COMPILER ${ARM_GCC_BIN_DIR}/arm-none-eabi-g++${TOOL_EXECUTABLE_SUFFIX} )#CACHE INTERNAL "C++ compiler")
SET(CMAKE_ASM_COMPILER ${ARM_GCC_BIN_DIR}/arm-none-eabi-gcc${TOOL_EXECUTABLE_SUFFIX} )#ACHE INTERNAL "Assembler compiler")
	

SET(CMAKE_OBJCOPY ${ARM_GCC_BIN_DIR}/arm-none-eabi-objcopy${TOOL_EXECUTABLE_SUFFIX} CACHE INTERNAL "objcopy tool")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
