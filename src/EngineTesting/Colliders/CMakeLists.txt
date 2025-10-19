add_executable(Colliders
        Colliders.cpp
)

target_link_libraries(Colliders PRIVATE Engine)

add_custom_command(
        TARGET Colliders POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory  # Use CMake's built-in, cross-platform copy tool
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"    # The source directory to copy from
        "$<TARGET_FILE_DIR:Colliders>/assets"  # The destination directory
)
