#pragma once

#include "../../dependencies/raylib/include/raylib.h"

#include <iostream>

class PlayerCamera
{
  public:
    Camera camera;

    void changeTarget(Vector3 newtarg)
    {
        this->camera.target = newtarg;
    }

    void changePosition(Vector3 newpos)
    {
        this->camera.position = newpos;
    }

    void logCamera()
    {
        std::cout << "Position is : " << this->camera.position.x << " " << this->camera.position.y << " "
                  << this->camera.position.z << std::endl;
        std::cout << "Target is : " << this->camera.target.x << " " << this->camera.target.y << " "
                  << this->camera.target.z << std::endl;
    }

    PlayerCamera()
    {
        this->camera.position = (Vector3){0.0f, 0.0f, 0.0f};
        this->camera.target = (Vector3){0.0f, 0.0f, 0.0f};
        this->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        this->camera.fovy = 45.0f;
        this->camera.projection = CAMERA_PERSPECTIVE;
    };
};