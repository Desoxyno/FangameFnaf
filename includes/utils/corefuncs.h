#pragma once

#include <raylib.h>

inline const bool IsButtonClicked(Rectangle rect)
{
    return CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}