file(GLOB TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(TEST_SOURCE IN ITEMS ${TEST_SOURCES})
    string(COMPARE NOTEQUAL ${TEST_SOURCE} "catch.cpp" _is_main_file)
    if(_is_main_file)
        string(REPLACE ".cpp" "" TEST_NAME ${TEST_SOURCE})
        add_executable(
            ${TEST_NAME}
            catch.cpp
            ${TEST_SOURCE}
        )
        target_link_libraries(${TEST_NAME} ${PROJECT_NAME})
        add_test(${TEST_NAME} ${TEST_NAME})
    endif()
endforeach()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR}/tests)