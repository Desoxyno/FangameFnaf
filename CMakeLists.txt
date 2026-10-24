cmake_minimum_required(VERSION 3.20)

project(FnafFangame VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

set(DISCORD_SDK_ROOT "${CMAKE_SOURCE_DIR}/dependencies/discord_social_sdk")
set(DISCORD_SDK_LIB_DIR "${DISCORD_SDK_ROOT}/lib/release")

set(DISCORD_ENABLED FALSE)

add_executable(FnafFangame main.cpp
    includes/ennemies/springtrap/node.cpp)

target_include_directories(FnafFangame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_include_directories(FnafFangame PRIVATE
    "${DISCORD_SDK_ROOT}/include"
)

target_compile_definitions(FnafFangame PRIVATE
    $<$<CONFIG:Debug>:DEBUG_BUILD>
    DISCORD_ENABLED=$<BOOL:${DISCORD_ENABLED}>
)

if(WIN32)
    set(DISCORD_SHARED_LIB "${DISCORD_SDK_LIB_DIR}/libdiscord_partner_sdk.so")
elseif(APPLE)
    set(DISCORD_SHARED_LIB "${DISCORD_SDK_LIB_DIR}/libdiscord_partner_sdk.dylib")
endif()
    set(DISCORD_SHARED_LIB "${DISCORD_SDK_LIB_DIR}/libdiscord_partner_sdk.so")

if(WIN32)

    target_link_libraries(FnafFangame PRIVATE
        opengl32
        gdi32
        winmm
        "${DISCORD_SDK_ROOT}/lib/release/libdiscord_partner_sdk.lib"
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
        "${DISCORD_SDK_ROOT}/lib/release/libdiscord_partner_sdk.dylib"
    )

elseif(UNIX)

    target_link_libraries(FnafFangame PRIVATE
        X11
        "${DISCORD_SDK_ROOT}/lib/release/libdiscord_partner_sdk.so"
    )
    
endif()

target_link_libraries(FnafFangame PRIVATE
    raylib
)

if(DISCORD_ENABLED)
    add_custom_command(TARGET FnafFangame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${DISCORD_SHARED_LIB}"
        $<TARGET_FILE_DIR:FnafFangame>
    )
endif()