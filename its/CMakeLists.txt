cmake_minimum_required(VERSION 3.10)

project(openc2x C CXX)

SET(PROJECT_VERSION_MAJOR "1")
SET(PROJECT_VERSION_MINOR "5")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++17")
SET(CMAKE_VERBOSE_MAKEFILE "ON")

SET(MAIN_SRCS
   main.cpp
)

find_package(Boost COMPONENTS date_time system thread)
find_package(Threads REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/common/asn1/
    ${CMAKE_CURRENT_BINARY_DIR}/common/buffers/
)

link_directories(
    ${Boost_LIBRARY_DIRS}
    ${ASN1C_EXECUTABLE}	
)

add_subdirectory(common)

add_executable (openc2x ${MAIN_SRCS})
target_link_libraries (openc2x PRIVATE
    proto
    asn
    boost_program_options
)
