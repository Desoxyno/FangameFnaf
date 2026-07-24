cmake_minimum_required(VERSION 3.20)

project(FnafFangame VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FnafFangame
    src/main.cpp

    src/scenes/intro.cpp
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
    src/game/systems/animatronics/springtrap.cpp
    src/game/systems/animatronics/animatronic.cpp
)

target_include_directories(FnafFangame PRIVATE
    src
)

if(WIN32)
    target_include_directories(FnafFangame PRIVATE
        dependencies/raylib-win/include)
    target_link_directories(FnafFangame PRIVATE
        dependencies/raylib-win/lib)
else()
    target_include_directories(FnafFangame PRIVATE
        dependencies/raylib-li/include)
    target_link_directories(FnafFangame PRIVATE
        dependencies/raylib-li/lib)
endif()

target_link_libraries(FnafFangame PRIVATE raylib)

if(WIN32)
    target_link_libraries(FnafFangame PRIVATE opengl32 gdi32 winmm)
    target_link_options(FnafFangame PRIVATE -static-libgcc -static-libstdc++ -static)
else()
    target_link_libraries(FnafFangame PRIVATE X11)
endif()