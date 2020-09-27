set(CMAKE_C_FLAGS_INIT "-mstm8 --out-fmt-elf  ")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-msoft-float  -mstm8 --out-fmt-elf --all-callee-saves --debug --verbose --stack-auto --fverbose-asm --float-reent --no-peep ")
add_definitions("-DTHUMB_INTERWORK")
add_definitions("-DSTM8")
add_definitions("-DSTM8L152")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -msoft-float -mstm8 --out-fmt-elf --all-callee-saves --debug --verbose --stack-auto --fverbose-asm --float-reent --no-peep ")

add_compile_options(
		-msoft-float
		-mstm8
		--out-fmt-elf
		 --all-callee-saves
		 --debug
		 --verbose
		 --stack-auto
		 --fverbose-asm
		 --float-reent
		 --no-peep
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -msoft-float --out-fmt-elf --all-callee-saves --debug --verbose --stack-auto --fverbose-asm --float-reent --no-peep ")

set(OPTIMIZATION_RELEASE "--opt-code-size")


link_directories(${COMPILER_LIB_DIR}/stm8)

# list all et(SOURCES)
foreach(module adapt_stm8 )
	file(GLOB_RECURSE TMP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${module}/*.c*)
	list(APPEND SOURCES ${TMP_SOURCES})
endforeach(module)


set(TARGET_LINK_LIBRARIES stm8)

