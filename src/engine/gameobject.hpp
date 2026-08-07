#pragma once

#include <string>

#include "raylib.h"
#include "raymath.h"

class GameObject
{
public:
    std::string name;

    enum class ObjectType {
        Generic,
        Springtrap,
        Camera, 
        Door
    };

    ObjectType type = ObjectType::Generic;
    
    Model model;
    BoundingBox bounds;
    ModelAnimation* animations = nullptr;
    int animationCount = 0;
    int currentFrame = 0;
    bool playingAnimation = false;
    Vector3 positionM = {0.0f, 0.0f, 0.0f};
    Vector3 rotationM = {0.0f, 0.0f, 0.0f};
    Vector3 scaleM = {1.0f, 1.0f, 1.0f};
    Vector3 pivotOffset = {0, 0, 0};
    float animFrameSpeed = 1;
    Matrix GetTransform() const
    {
        Matrix translation = MatrixTranslate(positionM.x, positionM.y, positionM.z);

        Matrix rotation = MatrixRotateXYZ({DEG2RAD * rotationM.x, DEG2RAD * rotationM.y, DEG2RAD * rotationM.z});

        Matrix scaleMatrix = MatrixScale(scaleM.x, scaleM.y, scaleM.z);

        Matrix pivot = MatrixTranslate(-pivotOffset.x, -pivotOffset.y, -pivotOffset.z);

        return MatrixMultiply(translation, MatrixMultiply(rotation, MatrixMultiply(pivot, scaleMatrix)));
    }
    void CalculatePivot()
    {
        BoundingBox box = GetModelBoundingBox(model);

        pivotOffset = {(box.min.x + box.max.x) / 2.0f, (box.min.y + box.max.y) / 2.0f, (box.min.z + box.max.z) / 2.0f};
    }
    virtual void Draw();
    virtual void Update();
    virtual void Exit();
    void DrawBounds();
};