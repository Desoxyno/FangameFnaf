cmake_minimum_required(VERSION 3.20)

project(FnafFangame VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/raylib)


add_executable(FnafFangame
    src/main.cpp

    src/scenes/mainmenu.cpp
    src/scenes/night1.cpp

    src/engine/scenemanager.cpp
    src/engine/shader.cpp
    src/engine/gameobject.cpp

    src/game/gamestate.cpp

    src/audio/soundloader.cpp

    src/utils/corefunc.cpp
    src/utils/dropdown.cpp

    src/debug/debug_mode.cpp

    src/game/systems/camera/camera_system.cpp
    src/game/systems/tablet/tablet.cpp
    src/game/systems/animatronics/springtrap.cpp
)

target_include_directories(FnafFangame PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/rlights
)

target_link_libraries(FnafFangame PRIVATE
    raylib
)

if(WIN32)

    target_link_libraries(FnafFangame PRIVATE
        opengl32
        gdi32
        winmm
    )

    target_link_options(FnafFangame PRIVATE
        -static-libgcc
        -static-libstdc++
    )

elseif(APPLE)

    target_link_libraries(FnafFangame PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )

elseif(UNIX)


    
endif()