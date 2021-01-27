set(CMAKE_C_FLAGS_INIT "")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-msoft-float  -mstm32 ")
add_definitions("-DTHUMB_INTERWORK")
add_definitions("-DSTM32")
add_definitions("-DSTM32F103xE")


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
add_compile_options(
        -mcpu=cortex-m3
		-mthumb
		-msoft-float
#		-mfloat-abi=hard
        -mthumb-interwork	
		-mfloat-abi=softfp
		-fstrict-volatile-bitfields
        -ffunction-sections
        -fdata-sections
        -fmessage-length=0
		-fdiagnostics-color=auto
        -ffreestanding
        -Werror=switch
        -Werror=uninitialized
        -Werror=maybe-uninitialized
		-pedantic 
		-Wextra 
		-fstrict-volatile-bitfields 
		-ffunction-sections 
		-fdata-sections 
		-fmessage-length=0 
        -fdiagnostics-show-option 
		-fdiagnostics-color=auto 
		-falign-functions=4
		-Werror=address 
		-Werror=cast-align 
        -Werror=return-type 
		-Werror=shift-count-negative 
		-Werror=shift-count-overflow 
		-Werror=shift-negative-value 
        -Werror=parentheses 
        -Werror=switch 
		-Werror=switch-bool 
		-Werror=switch-unreachable 
        -Werror=uninitialized 
        -Werror=maybe-uninitialized 
        -Werror=nonnull 
        -Werror=init-self 
        -Werror=sequence-point 
        -Werror=overflow 
        -Werror=unused-but-set-parameter 
		-Werror=stringop-overflow 
		-Werror=stringop-truncation 
        -Werror=bool-compare 
		-Werror=bool-operation 
#		-Werror=duplicated-branches 
		-Werror=duplicated-cond 
		-Werror=tautological-compare 
		-Werror=float-equal 
		-Werror=shadow 
		-Werror=dangling-else 
		-Werror=empty-body 
		-Werror=pointer-arith 
		-Werror=pointer-compare 
		-Werror=logical-op 
        -Werror=logical-not-parentheses 
		-Werror=missing-field-initializers 
		-Werror=missing-braces 
		-Werror=sizeof-pointer-div 
		-Werror=sizeof-pointer-memaccess 
		-Werror=sizeof-array-argument 
		-Werror=memset-elt-size 
		-Werror=memset-transposed-args 
		-Werror=volatile-register-var 
        -Werror=nonnull
		-Werror=stringop-overflow 
		-Werror=stringop-truncation
		-Werror=bool-operation 
        -Werror=init-self
        -Werror=sequence-point
        -Werror=overflow
        -Werror=unused-but-set-parameter
        -Werror=bool-compare
        -Werror=type-limits
        -Werror=logical-not-parentheses
        -Werror=enum-compare
		-Werror=empty-body 
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=missing-parameter-type")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=implicit -Werror=implicit-int")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=nested-externs")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=override-init")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=implicit-function-declaration")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -falign-functions=4")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=placement-new")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=extra-semi")

set(OPTIMIZATION_DEBUG "-O0")
set(OPTIMIZATION_RELEASE "-O0 ")

set(CMAKE_C_FLAGS_DEBUG " ${OPTIMIZATION_DEBUG} -g")
set(CMAKE_C_FLAGS_RELEASE " ${OPTIMIZATION_RELEASE} -g  ")
set(CMAKE_CXX_FLAGS_DEBUG " ${OPTIMIZATION_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE " ${OPTIMIZATION_RELEASE} -g")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fms-extensions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-use-cxa-atexit")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-threadsafe-statics")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${COMPILER_LIB_DIR}/thumb/v7/nofp")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${COMPILER_LIB_DIR}/thumb/v8-m.main+fp/softfp")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${COMPILER_LIB_DIR}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mcpu=cortex-m3")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mthumb")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T\"${CMAKE_CURRENT_SOURCE_DIR}/adapt_stm32/LinkerScript/stm32f103x8.ld\"")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=rdimon.specs")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nano.specs")

#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --gc-sections")

#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nano.specs")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lm")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage,-Map,${PROJECT_NAME}.map")
