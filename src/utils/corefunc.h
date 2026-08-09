#pragma once

#include "raylib.h"
#include "engine/gameobject.hpp"
#include "engine/player_camera.hpp"
#include "raymath.h"

const bool IsButtonClicked(Rectangle rect);
const bool IsButtonHovered(Rectangle rect);
const bool IsVisible(GameObject* object, PlayerCamera camera);