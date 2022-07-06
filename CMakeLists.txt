cmake_minimum_required(VERSION 3.15)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/engine
)

set(SOURCE_FILES
    "src/main.cpp"
    "src/engine/Engine.cpp"
    "src/engine/Window.cpp"
)

set(SFML_DIR C:/Programming/Languages/C++/SFML-2.5.1/lib/cmake/SFML)

find_package(SFML 2.5.1 COMPONENTS graphics audio system window REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-audio sfml-system sfml-window)
