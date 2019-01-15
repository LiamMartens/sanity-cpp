# define cpp sources
set(
    SANITYCPP_SOURCES
    sanity_object.cpp
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
    sanity_patch.cpp
    sanity_patch_set_mutation.cpp
    sanity_patch_unset_mutation.cpp
    sanity_patch_insert_mutation.cpp
    sanity_patch_math_mutation.cpp
    sanity_patch_diffmatch_mutation.cpp
    sanity_mutations.cpp
    sanity_modifiers.cpp
)

#  @add_library add library
add_library(${SANITYCPP_TARGET_NAME} SHARED ${SANITYCPP_SOURCES})

# @target_link_libraries link dependencies
target_link_libraries(${SANITYCPP_TARGET_NAME} ${CURL_LIBRARIES})
target_link_libraries(${SANITYCPP_TARGET_NAME} ${nlohmann_json_LIBRARIES})

# @install
install(
    TARGETS ${SANITYCPP_TARGET_NAME}
    EXPORT ${SANITYCPP_TARGETS_EXPORT_NAME}
    INCLUDES DESTINATION ${SANITYCPP_INCLUDE_INSTALL_DIR}
    LIBRARY DESTINATION ${SANITYCPP_LIB_INSTALL_DIR}
)

# @install
install(
    EXPORT ${SANITYCPP_TARGETS_EXPORT_NAME}
    DESTINATION ${SANITYCPP_CONFIG_INSTALL_DIR}
)