add_executable(FlappyBird
        FlappyBird.cpp
)

target_link_libraries(FlappyBird PRIVATE Engine)

add_custom_command(
        TARGET FlappyBird POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory  # Use CMake's built-in, cross-platform copy tool
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"    # The source directory to copy from
        "$<TARGET_FILE_DIR:FlappyBird>/assets"  # The destination directory
)
