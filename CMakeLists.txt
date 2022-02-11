cmake_minimum_required(VERSION 3.17)
project(cpp)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CPP_COMPILER gcc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage")

set(CMAKE_CXX_STANDARD 20)

################################################ AOC2015 Lib ###########################################################

file(GLOB AOC_2015_SRC_FILES
        src/public/2015/*.cpp
        src/private/2015/*.cpp
        src/private/utils/*.cpp
        src/private/template/*.cpp
        )

file(GLOB AOC_2015_HDR_PUBLIC
        inc/public/2015)
file(GLOB AOC_2015_HDR_PRIVATE
        inc/private/2015
        inc/private/utils
        inc/private/template)

file(GLOB EXTERNAL_SRC_FILES
        external/md5/src/*.cpp
        )

file(GLOB EXTERNAL_HDR
        external/md5/inc
        )


set(aoc_2015_lib_files ${AOC_2015_SRC_FILES} ${EXTERNAL_SRC_FILES})
add_library(AoC2015Lib STATIC ${aoc_2015_lib_files})
target_include_directories(AoC2015Lib
        PUBLIC
        ${AOC_2015_HDR_PUBLIC}
        PRIVATE
        ${AOC_2015_HDR_PRIVATE}
        ${EXTERNAL_HDR}
        )


################################################ AOC2015 Executable ####################################################
file(GLOB AOC_2015_EXE_SRC_FILES
        src/public/2015/*.cpp
        src/private/2015/*.cpp
        src/private/utils/*.cpp
        src/exe/2015/*.cpp
        )

set(aoc_2015_exe_files ${AOC_2015_EXE_SRC_FILES})
add_executable(AoC2015 ${AOC_2015_EXE_SRC_FILES})

target_link_libraries(AoC2015 LINK_PRIVATE AoC2015Lib)
target_include_directories(AoC2015
        PUBLIC
        ${AOC_2015_HDR_PUBLIC}
        PRIVATE
        ${AOC_2015_HDR_PRIVATE}
        ${EXTERNAL_HDR}
        )

add_custom_command(TARGET AoC2015 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/test/input_data $<TARGET_FILE_DIR:AoC2015>/input_data)

################################################ Unity Library #########################################################
file(GLOB UNITY_LIB_SOURCE_FILES
        test/tools/unity/src/*.c)

file(GLOB UNITY_LIB_HEADER_FILES
        test/tools/unity/inc
        )

set(unity_lib_files ${UNITY_LIB_SOURCE_FILES})
add_library(unity STATIC ${UNITY_LIB_SOURCE_FILES})
target_include_directories(unity
        PUBLIC
        ${UNITY_LIB_HEADER_FILES}
        )

################################################ AoC 2015 Tests Executable #############################################

file(GLOB INTERNAL_SOURCE_FILES
        test/unit_tests/src/*.cpp
        test/unit_tests/unit/*.cpp
        )

file(GLOB TEST_INTERNAL_HEADER_FILES
        test/unit_tests/inc
        )

set(TEST_INTERNAL_SOURCE_FILES ${INTERNAL_SOURCE_FILES})

add_executable(AoC2015Test ${TEST_INTERNAL_SOURCE_FILES})
target_link_libraries(AoC2015Test LINK_PRIVATE AoC2015Lib)
target_link_libraries(AoC2015Test LINK_PUBLIC unity)

target_include_directories(AoC2015Test
        PUBLIC
        ${UNITY_LIB_HEADER_FILES}
        ${TEST_INTERNAL_HEADER_FILES}

        ${AOC_2015_HDR_PUBLIC}
        ${AOC_2015_HDR_PRIVATE}
        ${EXTERNAL_HDR}
        )

add_custom_command(TARGET AoC2015Test PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/test/input_data $<TARGET_FILE_DIR:AoC2015Test>/input_data)