cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake"
     "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/share/modules/cmake"
     "/usr/share/zkllvm")

include(CMConfig)
include(CMSetupVersion)
include(CircuitCompile)

cm_workspace(crypto3)

macro(cm_find_package NAME)
    if(NOT "${NAME}" MATCHES "^${CMAKE_WORKSPACE_NAME}_.*$" AND NOT "${NAME}" STREQUAL CM)
        find_package(${ARGV})
    else()
        set(${ARGV0}_FOUND ON CACHE BOOL "")
    endif()
endmacro()

cm_setup_version(VERSION 0.1.0 PREFIX ${CMAKE_WORKSPACE_NAME})

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/libs/crypto3")

#Example directories
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/main")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/arithmetics_add")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/arithmetics_mul")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/binary")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/charcpp")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/charcpp_array")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/globals")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/mutable_globals_2")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/mutable_globals_3")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/mutable_globals_4")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/mutable_globals_5")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/mutable_globals_6")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/mutable_globals_7")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/mutable_globals_8")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/mutable_globals_9")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/mutable_globals_10")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/ptr")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/no_IO_in_wrapper")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/wrapper_not_called")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src/for_loop")
