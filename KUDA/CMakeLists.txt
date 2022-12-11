project(KUDA)

set(SOURCE_FILES
        src/window.cpp
        src/renderer.cpp
        src/actor.cpp
        src/camera.cpp
        src/lightingAnalyzer.cpp
        src/sceneRenderer.cpp
        src/menuRenderer.cpp
        src/pawn.cpp
        src/pawnController.cpp
        src/ray.cpp
        src/raycasting2DRenderer.cpp
        src/raycastingRenderer.cpp
        src/renderer3D.cpp
        src/simple2DRenderer.cpp
        src/textureAtlas.cpp
        src/wallSpriteFactory.cpp
	)

set(SFML_ROOT c:/SFML)

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

target_include_directories(${PROJECT_NAME} PRIVATE include/KUDA)
target_include_directories(${PROJECT_NAME} PUBLIC include)