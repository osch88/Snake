cmake_minimum_required(VERSION 3.0.0)
project(snake VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (SOURCES
    src/main.cpp
    src/engine.cpp
    src/input.cpp
    src/snake.cpp
    src/food.cpp
    src/scoreboard.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(include)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
