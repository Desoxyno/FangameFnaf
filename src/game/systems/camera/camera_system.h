#pragma once

#include <array>

#include "securitycamera.h"

class Camera_System
{
private:
    int current_camera = 0;
    std::array<SecurityCamera, 2> cameras;

public:
    void InitializeCameras();

    void Update();

    SecurityCamera& GetCurrentCamera()
    {
        return cameras[current_camera];
    }
};