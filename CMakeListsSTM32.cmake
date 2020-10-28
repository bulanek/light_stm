set(CMAKE_C_FLAGS_INIT "")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-msoft-float  -mstm32 ")
add_definitions("-DTHUMB_INTERWORK")
add_definitions("-DSTM32")
add_definitions("-DSTM32F103xB")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -msoft-float -mstm32 ")

add_compile_options(
		-msoft-float
        -mcpu=cortex-m3
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -msoft-float ")

link_directories(${COMPILER_LIB_DIR})

# list all et(SOURCES)
foreach(module adapt_stm32 )
	file(GLOB_RECURSE TMP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${module}/*.c*)
	list(APPEND SOURCES ${TMP_SOURCES})
endforeach(module)

set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/adapt_stm32/CMSIS/device/startup_stm32f103xb.s)


include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/adapt_stm32/CMSIS/core 
${CMAKE_CURRENT_SOURCE_DIR}/adapt_stm32/CMSIS/device
)

set(TARGET_LINK_LIBRARIES )


set(OPTIMIZATION_DEBUG "-O0")
set(OPTIMIZATION_RELEASE "-O2 ")

set(CMAKE_C_FLAGS_DEBUG " ${OPTIMIZATION_DEBUG} -g")
set(CMAKE_C_FLAGS_RELEASE " ${OPTIMIZATION_RELEASE} -g  ")
set(CMAKE_CXX_FLAGS_DEBUG " ${OPTIMIZATION_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE " ${OPTIMIZATION_RELEASE} -g")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fms-extensions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-use-cxa-atexit")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-threadsafe-statics")

#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${COMPILER_LIB_DIR}/thumb/v7/nofp")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mcpu=cortex-m3")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mthumb")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T\"${CMAKE_CURRENT_SOURCE_DIR}/adapt_stm32/LinkerScript/stm32f103x8.ld\"")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=rdimon.specs")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections,-lm,-lc,--print-memory-usage,-Map,${PROJECT_NAME}.map")


