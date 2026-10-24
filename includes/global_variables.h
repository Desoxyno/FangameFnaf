#pragma once


#include <raylib.h>
#include <cstdint>
#include "discordpp.h"

const uint64_t APPLICATION_ID = 1563181428114595890;

enum Scenes {
    NO_CHANGE,
    MAIN_MENU,
    NIGHT1
};

enum Node_Names {
    Basement,
    OfficeLeft,
    OfficeFront,
    HallwayEmployees,
    HallwayService,
    PartsService
};

static uint8_t lightCount = 0;

constexpr Shader shader{};
constexpr uint8_t NIGHT_DURATION = 50;
constexpr uint8_t HOURS_PER_NIGHT = 6;
constexpr uint8_t current_night = 1;