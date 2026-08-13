#pragma once

#include <cfloat>
#include <cmath>
#include <string>

#include "engine/player_camera.hpp"
#include "r3d/r3d.h"
#include "raylib.h"
#include "raymath.h"
#include "utils/corefunc.h"
#include "utils/global_variable.h"

class GameObject
{
public:
    std::string name;

    enum class ObjectType
    {
        Structure,
        Object,
        Springtrap,
        Camera,
        Door
    };

    ObjectType type = ObjectType::Structure;

    R3D_Model model;
    R3D_BoundingBox bounds;
    R3D_BoundingBox box;
    ModelAnimation* animations = nullptr;
    int animationCount = 0;
    int currentFrame = 0;
    bool playingAnimation = false;
    Vector3 positionM = {0.0f, 0.0f, 0.0f};
    Vector3 rotationM = {0.0f, 0.0f, 0.0f};
    Vector3 scaleM = {1.0f, 1.0f, 1.0f};
    Vector3 pivotOffset = {0, 0, 0};
    float animFrameSpeed = 1;

    Texture2D albedo;
    Texture2D normal;
    Texture2D orm;

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
        const BoundingBox& box_plch = model.aabb;

        Vector3 center = Vector3Scale(Vector3Add(box_plch.min, box_plch.max), 0.5f);

        Vector3 halfExtent = Vector3Scale(Vector3Subtract(box_plch.max, box_plch.min), 0.5f);

        pivotOffset = center;
        box = R3D_GetBoundingBox(center, halfExtent);
    }
    virtual void Draw(PlayerCamera& camera);
    virtual void Update();
    virtual void Exit();
    void DrawBounds();
};