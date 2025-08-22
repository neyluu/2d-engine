# Generate compile_commands.json
set(
    CMAKE_EXPORT_COMPILE_COMMANDS ON
    CMAKE_CXX_FLAGS  "-Wall -pedantic -fno-elide-constructors -ggdb"
)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    endif()
endif()

add_library(Engine)

target_sources(Engine PRIVATE
        Inc/Engine/Core.h
        Inc/Engine/Entities.h

        Src/Engine.cpp
        Src/Engine.h

        Src/Configs/Settings.h

        Src/Entities/GameObject.cpp
        Src/Entities/GameObject.h
        Src/Entities/Sprite.cpp
        Src/Entities/Sprite.h
        Src/Entities/Drawable.cpp
        Src/Entities/Drawable.h
        Src/Entities/Colliders/Collider.cpp
        Src/Entities/Colliders/Collider.h
        Src/Entities/Colliders/BoxCollider.cpp
        Src/Entities/Colliders/BoxCollider.h
        Src/Entities/RigidBody.cpp
        Src/Entities/RigidBody.h
        Src/Entities/Colliders/ColliderManager.cpp
        Src/Entities/Colliders/ColliderManager.h
        Src/Entities/Colliders/CircleCollider.cpp
        Src/Entities/Colliders/CircleCollider.h
        Src/Entities/Transform.cpp
        Src/Entities/Transform.h

        Src/Scenes/Scene.cpp
        Src/Scenes/Scene.h
        Src/Scenes/SceneManager.h
        Src/Scenes/ISceneManager.h
)

target_link_libraries(Engine PUBLIC raylib)
target_include_directories(Engine PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Inc"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src"
)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()