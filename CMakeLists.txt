cmake_minimum_required(VERSION 3.20)

project(FnafFangame VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FnafFangame
    src/scenes/intro.cpp
    src/scenes/mainmenu.cpp
    src/scenes/scenemanager.cpp
    src/core/shader.cpp
    src/core/soundloader.cpp
    src/core/corefunc.cpp) 

target_sources(FnafFangame PRIVATE 
    src/main.cpp
    src/core/camera.hpp
    src/core/gameobject.hpp
    src/core/config.h
    src/core/gamestate.h
    src/scenes/intro.h
    src/scenes/mainmenu.h
    src/scenes/scene.hpp
    src/scenes/scenemanager.h
    src/core/shader.h
    src/core/soundload.h
    src/core/corefunc.h
)

target_include_directories(FnafFangame PRIVATE dependencies/raylib/include)

target_link_directories(FnafFangame PRIVATE dependencies/raylib/lib)

target_link_libraries(FnafFangame PRIVATE raylib X11)