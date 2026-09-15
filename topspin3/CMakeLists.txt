cmake_minimum_required(VERSION 3.25)
project(top_spin_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(generated/rexglue.cmake)
include(../framework/cmake/Recomp.cmake)

recomp_add_game(top_spin_3
    OUTPUT_NAME "Top Spin 3"
    SOURCES
        src/main.cpp
    SETTINGS "${CMAKE_CURRENT_SOURCE_DIR}/settings/top_spin_3.toml"
    ICON "${CMAKE_CURRENT_SOURCE_DIR}/metadata/top_spin_3.ico"
    RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/top_spin_3.rc"
    DEVELOPMENT_GAME_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/assets"
)
