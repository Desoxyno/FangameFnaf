#pragma once

#include "engine/gameobject.hpp"
#include "engine/player_camera.hpp"
#include "raylib.h"
#include "raymath.h"

const bool IsButtonClicked(Rectangle rect);
const bool IsButtonHovered(Rectangle rect);
bool IsVisible(R3D_Mesh mesh, Matrix transform, PlayerCamera& camera);