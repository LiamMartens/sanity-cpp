cmake_minimum_required(VERSION 3.1)

# @project
project(sanitycpp VERSION 1.8.1)

# @option add options
option(BUILD_TESTS "Build tests" ON)

# @set add flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# @set configuration variables
set(SANITYCPP_TARGET_NAME ${PROJECT_NAME})
set(SANITYCPP_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/sanitycpp")
set(SANITYCPP_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(SANITYCPP_TESTS_DIR "${PROJECT_SOURCE_DIR}/tests")

# @set install destinations
set(SANITYCPP_CONFIG_INSTALL_DIR "lib/cmake/${PROJECT_NAME}")
set(SANITYCPP_INCLUDE_INSTALL_DIR "include")
set(SANITYCPP_INCLUDE_INSTALL_DIR_REAL "${CMAKE_INSTALL_PREFIX}/${SANITYCPP_INCLUDE_INSTALL_DIR}/${SANITYCPP_TARGET_NAME}")
set(SANITYCPP_LIB_INSTALL_DIR "lib")

# @set cmake config variables
set(SANITYCPP_TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(SANITYCPP_CMAKE_CONFIG_TEMPLATE "cmake/config.cmake.in")
set(SANITYCPP_CMAKE_CONFIG_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(SANITYCPP_CMAKE_VERSION_CONFIG_FILE "${SANITYCPP_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(SANITYCPP_CMAKE_PROJECT_CONFIG_FILE "${SANITYCPP_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake")
set(SANITYCPP_CMAKE_PROJECT_TARGETS_FILE "${SANITYCPP_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake")

# @find_package find dependencies
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# @include_directories include dependency includes
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${nlohmann_json_INCLUDE_DIRS})

# @add_subdirectory include headers
include_directories(${SANITYCPP_INCLUDE_DIR})
file(GLOB HEADER_LIST "${SANITYCPP_INCLUDE_DIR}/*.h")

# @add_subdirectory include srcs
add_subdirectory(${SANITYCPP_SRC_DIR})

# @if check if tests need to be built
if(BUILD_TESTS)
    # @enable_testing
    enable_testing()
    # @add_subdirectory Add test sources
    add_subdirectory(${SANITYCPP_TESTS_DIR})
endif()

# @include Add cmake helpers
include(CMakePackageConfigHelpers)

# @write_basic_package_version_file Writes a default version config
write_basic_package_version_file(
    ${SANITYCPP_CMAKE_VERSION_CONFIG_FILE} COMPATIBILITY SameMajorVersion
)

# @configure_file Configure the config file
configure_file(
    ${SANITYCPP_CMAKE_CONFIG_TEMPLATE}
    ${SANITYCPP_CMAKE_PROJECT_CONFIG_FILE}
    @ONLY
)

# @install install headers
install(
    DIRECTORY include/${SANITYCPP_TARGET_NAME}
    DESTINATION ${SANITYCPP_INCLUDE_INSTALL_DIR}
)

install(
    FILES ${SANITYCPP_CMAKE_PROJECT_CONFIG_FILE} ${SANITYCPP_CMAKE_VERSION_CONFIG_FILE}
    DESTINATION ${SANITYCPP_CONFIG_INSTALL_DIR}
)

# @export
export(
    TARGETS ${SANITYCPP_TARGET_NAME}
    FILE ${SANITYCPP_CMAKE_PROJECT_TARGETS_FILE}
)

export(
    PACKAGE
    ${SANITYCPP_TARGET_NAME}
)