cmake_minimum_required(VERSION 3.30.1)
project(draft)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig)

pkg_check_modules(SDL REQUIRED sdl2)

include_directories(${SDL_INCLUDE_DIRS})
include_directories(inc)

add_executable(prg
    main.cpp
    src/event.cpp
    src/game.cpp
    src/grid.cpp
    src/parse.cpp
    src/win.cpp
)

target_link_libraries(prg ${SDL_LIBRARIES} m)
