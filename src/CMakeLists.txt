# define cpp sources
set(
    SANITYCPP_SOURCES
    sanity_url.cpp
    sanity_string.cpp
    sanity_path.cpp
    sanity_slice.cpp
    sanity_client.cpp
    sanity_request.cpp
    sanity_equality_filter.cpp
    sanity_boolean_filter.cpp
    sanity_in_filter.cpp
    sanity_defined_filter.cpp
    sanity_match_filter.cpp
    sanity_order.cpp
    sanity_filter.cpp
    sanity_conditional.cpp
    sanity_query.cpp
    sanity_object_projection.cpp
    sanity_references_filter.cpp
    sanity_select.cpp
    sanity_create.cpp
    sanity_delete.cpp
)

add_library(${PROJECT_NAME} SHARED ${SANITYCPP_SOURCES})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${nlohmann_json_LIBRARIES})
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)