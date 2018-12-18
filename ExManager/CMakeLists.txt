project(FirstExample)
cmake_minimum_required(VERSION 2.6)

# This assumes you have library on the same folder as your project
add_subdirectory(googletest-release-1.8.1) # Google Test Library
include_directories(googletest/include googlemock/include)

set(CMAKE_CXX_STANDARD 11)          # C++ V11
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

set(SRCS main.cpp Portfolio.cpp Portfolio.h PortfolioTest.cpp)

add_executable(test ${SRCS})
target_link_libraries(test pthread)
target_link_libraries(test gmock gmock_main)
target_link_libraries(test gtest gtest_main)
