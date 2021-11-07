#cmake_minimum_required(VERSION 3.0.0)
cmake_minimum_required(VERSION 3.19.0)
project(hlsyn VERSION 0.1.0)

#include(CTest)
#enable_testing()
include_directories(src)
file(GLOB SOURCES "src/*.cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./src")
add_executable(hlsyn ${SOURCES})


#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
