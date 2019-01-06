cmake_minimum_required(VERSION 3.10)

project(sanitycpp)
option(BUILD_TESTS "Build tests" ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

find_package(nlohmann_json REQUIRED)
include_directories(${nlohmann_json_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB HEADER_LIST "${CMAKE_SOURCE_DIR}/include/*.h")
install(FILES ${HEADER_LIST} DESTINATION include)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

# add tests dir
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif()