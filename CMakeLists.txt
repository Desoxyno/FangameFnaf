cmake_minimum_required(VERSION 3.20)

project(FnafFangame VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FnafFangame
    src/intro.cpp
    src/mainmenu.cpp
    src/scenemanager.cpp
    src/shader.cpp)

target_sources(FnafFangame PRIVATE 
    src/main.cpp
    src/camera.hpp
    src/gameobject.hpp
    src/config.h
    src/gamestate.h
    src/intro.h
    src/mainmenu.h
    src/scene.hpp
    src/scenemanager.hpp
    src/shader.hpp
)

target_include_directories(FnafFangame PRIVATE dependencies/raylib/include)

target_link_directories(FnafFangame PRIVATE dependencies/raylib/lib)

target_link_libraries(FnafFangame PRIVATE raylib X11)