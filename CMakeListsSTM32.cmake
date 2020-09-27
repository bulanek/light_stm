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

include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/adapt_stm32/CMSIS/core 
${CMAKE_CURRENT_SOURCE_DIR}/adapt_stm32/CMSIS/device
)

set(TARGET_LINK_LIBRARIES )

