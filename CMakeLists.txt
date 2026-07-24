cmake_minimum_required(VERSION 3.20)

project(FnafFangame VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FnafFangame
    src/main.cpp
    src/scenes/mainmenu.cpp
    src/scenes/night1.cpp

    src/engine/scenemanager.cpp
    src/engine/shader.cpp

    src/game/gamestate.cpp

    src/audio/soundloader.cpp

    src/utils/corefunc.cpp

    src/debug/debug_mode.cpp
    src/game/systems/camera/camera_system.cpp
    src/game/systems/tablet/tablet.cpp
    src/engine/gameobject.cpp
    src/utils/dropdown.cpp
)

target_include_directories(FnafFangame PRIVATE
    dependencies/raylib/include
    src
)

target_link_directories(FnafFangame PRIVATE
    dependencies/raylib/lib
)

target_link_libraries(FnafFangame PRIVATE
    raylib
    X11
)