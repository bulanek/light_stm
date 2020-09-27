# Targeting an embedded system, no OS.
set(CMAKE_SYSTEM_NAME Generic)

#Not used, only for possibility of further usage in projects
set(CMAKE_SYSTEM_PROCESSOR arm)

set(BIN_SUFFIX)
set (COMPILER_HOME "/usr" )
if (WIN32)
	set(COMPILER_HOME "C:/Program\ Files/SDCC")
endif()


set(COMPILER_BIN_DIR ${COMPILER_HOME}/bin )
set(COMPILER_INC_DIR ${COMPILER_HOME}/include)
set(COMPILER_LIB_DIR ${COMPILER_HOME}/lib)

if (NOT WIN32)
set(SDCC_BIN_DIR ${SDCC_HOME}/bin )
set(SDCC_INC_DIR ${SDCC_HOME}/share/sdcc/include)
set(SDCC_LIB_DIR ${SDCC_HOME}/share/sdcc/lib)
endif()


SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)


SET(CMAKE_C_COMPILER ${COMPILER_BIN_DIR}/sdcc.exe )
SET(CMAKE_ASM_COMPILER ${COMPILER_BIN_DIR}/sdcc.exe )

set(CMAKE_C_COMPILER_WORKS 1)

SET(CMAKE_OBJCOPY ${ARM_GCC_BIN_DIR}/arm-none-eabi-objcopy${BIN_SUFFIX} CACHE INTERNAL "objcopy tool")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


include_directories(${ARM_GCC_INC_DIR} ${ARM_GCC_INC_DIR}/c++/*)
