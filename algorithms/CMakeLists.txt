cmake_minimum_required(VERSION 3.16.4)

project(alg VERSION 1.0.0)

# Collect all source files in the module directory
file(GLOB MODULE_FILES *.c)

# Add to global SOURCES
add_library(${PROJECT_NAME} ${MODULE_FILES})

# Add include path for module headers
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)



