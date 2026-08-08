#pragma once
#include "raylib.h"

constexpr float NIGHT_DURATION = 50.0f;
constexpr int HOURS_PER_NIGHT = 6;
inline bool InDebug = false;
inline CameraMode camera_mode = CAMERA_CUSTOM;
inline bool useOptimisations = true;