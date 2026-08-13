#include "corefunc.h"

const bool IsButtonClicked(Rectangle rect)
{
    return CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

const bool IsButtonHovered(Rectangle rect)
{
    return CheckCollisionPointRec(GetMousePosition(), rect);
}

bool IsVisible(R3D_Mesh mesh, Matrix transform, PlayerCamera& camera)
{
    R3D_Frustum frustum = R3D_GetFrustum();

    R3D_OrientedBox box = R3D_GetOrientedBox(mesh.aabb, transform);

    return R3D_FrustumIntersectsOrientedBox(&frustum, box);
}