#include "dropdown.h"

bool Dropdown::Update()
{
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        // Bouton principal
        if (CheckCollisionPointRec(mouse, rect))
        {
            opened = !opened;
            return false;
        }

        if (opened)
        {
            for (int i = 0; i < items.size(); i++)
            {
                Rectangle itemRect = {rect.x, rect.y + rect.height * (i + 1), rect.width, rect.height};

                if (CheckCollisionPointRec(mouse, itemRect))
                {
                    selected = i;
                    opened = false;
                    return true;
                }
            }

            // Clic en dehors
            opened = false;
        }
    }

    return false;
}

void Dropdown::Draw()
{
    DrawRectangleRec(rect, DARKGRAY);
    DrawRectangleLinesEx(rect, 2, WHITE);

    DrawText(items[selected].c_str(), rect.x + 8, rect.y + 8, 20, WHITE);

    if (!opened)
    {
        return;
    }

    for (int i = 0; i < items.size(); i++)
    {
        Rectangle itemRect = {rect.x, rect.y + rect.height * (i + 1), rect.width, rect.height};

        Color color = DARKGRAY;

        if (CheckCollisionPointRec(GetMousePosition(), itemRect))
        {
            color = GRAY;
        }

        DrawRectangleRec(itemRect, color);
        DrawRectangleLinesEx(itemRect, 2, WHITE);

        DrawText(items[i].c_str(), itemRect.x + 8, itemRect.y + 8, 20, WHITE);
    }
}