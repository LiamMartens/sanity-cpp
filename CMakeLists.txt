cmake_minimum_required(VERSION 3.10)

project(sanitycpp)
option(BUILD_TESTS "Build tests" ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(PROJECT_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(PROJECT_TESTS_DIR "${PROJECT_SOURCE_DIR}/tests")

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

find_package(nlohmann_json REQUIRED)
include_directories(${nlohmann_json_INCLUDE_DIRS})

include_directories(${PROJECT_INCLUDE_DIR})
file(GLOB HEADER_LIST "${PROJECT_INCLUDE_DIR}/*.h")
add_subdirectory(${PROJECT_SRC_DIR})
install(
    FILES ${HEADER_LIST}
    DESTINATION include/sanity
)

# add tests dir
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(${PROJECT_TESTS_DIR})
endif()