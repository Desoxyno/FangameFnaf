#include "corefunc.h"

bool IsButtonClicked(Rectangle rect)
{
    return CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}