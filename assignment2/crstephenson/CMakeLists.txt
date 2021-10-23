#cmake_minimum_required(VERSION 3.0.0)
cmake_minimum_required(VERSION 3.20.0)
project(pleaseWork VERSION 0.1.0)

#include(CTest)
#enable_testing()
include_directories(src)
file(GLOB SOURCES "src/*.cpp")
add_executable(pleaseWork ${SOURCES}, ../dpgen.cpp)

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
