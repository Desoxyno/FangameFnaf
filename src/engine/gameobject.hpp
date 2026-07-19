#pragma once

#include <string>

#include "raylib.h"
#include "raymath.h"

class GameObject
{
public:
    std::string name;
    Model model;
    BoundingBox bounds;
    ModelAnimation* animations = nullptr;
    int animationCount = 0;
    Vector3 positionM = {0.0f, 0.0f, 0.0f};
    Vector3 rotationM = {0.0f, 0.0f, 0.0f};
    Vector3 scaleM = {1.0f, 1.0f, 1.0f};
    Matrix GetTransform() const
    {
        Matrix translation = MatrixTranslate(positionM.x, positionM.y, positionM.z);

        Matrix rotation = MatrixRotateXYZ({DEG2RAD * rotationM.x, DEG2RAD * rotationM.y, DEG2RAD * rotationM.z});

        Matrix scaleMatrix = MatrixScale(scaleM.x, scaleM.y, scaleM.z);

        return MatrixMultiply(translation, MatrixMultiply(rotation, scaleMatrix));
    }
};