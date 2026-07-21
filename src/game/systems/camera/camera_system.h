#pragma once

#include <array>

#include "securitycamera.h"

class Camera_System
{
public:
    SecurityCamera* current_camera;
    std::array<SecurityCamera, 2> cameras;
};