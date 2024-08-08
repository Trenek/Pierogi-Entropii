cmake_minimum_required(VERSION 3.26)

project(PierogiEntropii C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

include_directories(
    "${CMAKE_SOURCE_DIR}/source"
    "${CMAKE_SOURCE_DIR}/source/additions"
    "${CMAKE_SOURCE_DIR}/source/additions/drawMenuElement"
    "${CMAKE_SOURCE_DIR}/source/additions/textures"
    "${CMAKE_SOURCE_DIR}/source/cancelKey"
    "${CMAKE_SOURCE_DIR}/source/gridTile"
    "${CMAKE_SOURCE_DIR}/source/map"
    "${CMAKE_SOURCE_DIR}/source/player"
)

add_executable(PierogiEntropii
    "${CMAKE_SOURCE_DIR}/source/main.c"
    "${CMAKE_SOURCE_DIR}/source/additions/drawMenuElement/drawMenuElement.c"
    "${CMAKE_SOURCE_DIR}/source/additions/textures/textures.c"
    "${CMAKE_SOURCE_DIR}/source/cancelKey/cancelKey.c"
    "${CMAKE_SOURCE_DIR}/source/gridTile/gridTile.c"
    "${CMAKE_SOURCE_DIR}/source/map/map.c"
    "${CMAKE_SOURCE_DIR}/source/player/player.c"
    "${CMAKE_SOURCE_DIR}/source/stage/endScreen.c"
    "${CMAKE_SOURCE_DIR}/source/stage/equipment.c"
    "${CMAKE_SOURCE_DIR}/source/stage/menu.c"
    "${CMAKE_SOURCE_DIR}/source/stage/pause.c"
    "${CMAKE_SOURCE_DIR}/source/stage/play.c"
    "${CMAKE_SOURCE_DIR}/source/stage/time.c"
)

set(CMAKE_C_FLAGS "-W -Wall -Wextra -Wshadow -O2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -std=c23 -mwindows")

target_include_directories(PierogiEntropii PRIVATE
    "${CMAKE_SOURCE_DIR}/dependencies/raylib/include"
)

target_link_libraries(PierogiEntropii PRIVATE
    "${CMAKE_SOURCE_DIR}/dependencies/raylib/lib/libraylib.a"
    winmm
)

file (COPY "${CMAKE_SOURCE_DIR}/resources" "${CMAKE_SOURCE_DIR}/stage"
    DESTINATION "${CMAKE_BINARY_DIR}")