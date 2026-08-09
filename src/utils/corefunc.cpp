#include "corefunc.h"

const bool IsButtonClicked(Rectangle rect)
{
    return CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

const bool IsButtonHovered(Rectangle rect)
{
    return CheckCollisionPointRec(GetMousePosition(), rect);
}

const bool IsVisible(GameObject* object, PlayerCamera camera) {

    BoundingBox box = GetModelBoundingBox(object->model);
    Vector3 center = {
        (box.min.x + box.max.x) / 2.0f,
        (box.min.y + box.max.y) / 2.0f,
        (box.min.z + box.max.z) / 2.0f
    };

    float distance = Vector3Distance(center, camera.camera.position);

    if (distance > 50) {
        return false;
    }

    Vector3 toObject = Vector3Normalize(Vector3Subtract(center, camera.camera.position));

    Vector3 cameraDirection = Vector3Normalize(Vector3Subtract(camera.camera.target, camera.camera.position));

    float dot = Vector3DotProduct(cameraDirection, toObject);
    float halfFov = (camera.camera.fovy * DEG2RAD) / 2.0f;

    if (dot < cosf(halfFov))
        return false;

    return true;
}