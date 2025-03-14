#Project version minimum
cmake_minimum_required(VERSION 3.16.4)
set(PROJ_PATH ${CMAKE_CURRENT_SOURCE_DIR})
#Project name
project(test_algorythmes VERSION 1.0.0)

if(NOT DEFINED THREADX_PORT_PATH)
    set(THREADX_PORTS_PATH "threadx/ports")
    set(THREADX_PORT_INC_PATH ${THREADX_PORTS_PATH}/${THREADX_ARCH}/${THREADX_TOOLCHAIN}/inc)
endif()

#source files directory
set(SOURCES "main/main.cpp")
set(INCLUDE_DIRECTORIES 
    "main/inc" "threadx/common/inc" 
    ${THREADX_PORT_INC_PATH})

if(CHECK_SORT_ALGORITHMS)
    message("CHECK_SORT_ALGORITHMS is " ${CHECK_SORT_ALGORITHMS})
    add_definitions(-DCHECK_SORT_ALGORITHMS=1)
    add_subdirectory(algorithms)
endif()
if(CHECK_DATA_STRUCTURES)
    message("CHECK_DATA_STRUCTURES is " ${CHECK_DATA_STRUCTURES})
    add_definitions(-DCHECK_DATA_STRUCTURES=1)
    add_subdirectory(data_structures)
endif()

add_definitions(-DTX_LINUX_MULTI_CORE)

add_subdirectory(threadx)

set(ALL_FILES ${SOURCES})
add_executable(${PROJECT_NAME} ${ALL_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORIES})

target_link_libraries(${PROJECT_NAME} threadx pthread stdc++)

if(CHECK_SORT_ALGORITHMS)
    target_link_libraries(${PROJECT_NAME} alg)
endif()

if(CHECK_DATA_STRUCTURES)
    target_link_libraries(${PROJECT_NAME} dts)
endif()
