cmake_minimum_required(VERSION 3.15)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions()

if(MSVC)
    add_compile_options(/WX)
else()
    add_compile_options(-Wall -Wextra)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(SOURCE_FILES
    "src/main.cpp"    
    "src/engine/Assets.cpp"
    "src/engine/Window.cpp"
    "src/engine/Core.cpp"
    "src/engine/StateMachine.cpp"
    "src/engine/State.cpp"
    "src/engine/Renderer.cpp"
    "src/engine/Store.cpp"
    "src/engine/Object.cpp"
    "src/engine/Component.cpp"
    "src/engine/components/Animator.cpp"
    "src/engine/components/Collider.cpp"
    "src/engine/components/Physics.cpp"
    "src/engine/drawables/Sprite.cpp"
    "src/engine/drawables/Shape.cpp"
    "src/engine/drawables/RectangleShape.cpp"
    "src/engine/drawables/CircleShape.cpp"
    "src/engine/drawables/Arc.cpp"
    "src/engine/drawables/Text.cpp"
    "src/engine/components/Animation.cpp"
    "src/animations/Bezier.cpp"
    "src/animations/BezierScale.cpp"
    "src/animations/BezierFillColor.cpp"
    "src/engine/components/Bezier.cpp"
    "src/UI/Button.cpp"
    "src/UI/ProgressBar.cpp"

    # Application
    "src/states/Settings.cpp"
    "src/states/Character.cpp"
    "src/states/menu/MenuState.cpp"
    "src/states/game/GameState.cpp"
    "src/states/game/GameOverState.cpp"
    
    "src/states/game/gamestates/GamePlayState.cpp"
    "src/states/game/gamestates/GamePausedState.cpp"
    "src/states/game/gamestates/gameplaystates/GamePlayLookAroundState.cpp"
    "src/states/game/gamestates/gameplaystates/GamePlaySelectState.cpp"
    "src/states/description/DescriptionState.cpp"
    "src/animations/BezierOutlineColor.cpp"
    "src/states/CharacterCallbacks.cpp"
        src/states/BoardGameManager.cpp src/states/Tile.cpp src/states/TileManager.cpp)

set(SFML_DIR ./dependencies/SFML-2.5.1/lib/cmake/SFML)

find_package(SFML 2.5.1 COMPONENTS graphics audio system window REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-audio sfml-system sfml-window)
