cmake_minimum_required(VERSION 3.10)

project(sim C CXX)

set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -std=c++17 -fpermissive")
set(CMAKE_VERBOSE_MAKEFILE "ON")

find_package(eCAL REQUIRED)

set(MAIN_SRCS simulator_main.cpp)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_BINARY_DIR}/common/buffers
    ${PROJECT_SOURCE_DIR}/event-driven
    ${PROJECT_SOURCE_DIR}/fsm
    ${PROJECT_SOURCE_DIR}/mocking
    ${PROJECT_SOURCE_DIR}/network
    ${PROJECT_SOURCE_DIR}/simulator
)

add_subdirectory(common)
add_subdirectory(event-driven)
add_subdirectory(fsm)
add_subdirectory(mocking)
add_subdirectory(network)
add_subdirectory(simulator)

add_executable(sim ${MAIN_SRCS})
target_link_libraries (sim PRIVATE
    its-sim
    its-mocking
    its-network
    eCAL::core
)