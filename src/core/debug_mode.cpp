#include "debug_mode.h"

void DebugMode::ActivateDebugMode()
{
    if (!collision.hit)
    {
        ray = GetScreenToWorldRay(GetMousePosition(), camera);
    }
}

void DebugMode::Update()
{
    UpdateCamera(&camera, CAMERA_FREE);
}

void DebugMode::Draw()
{
    BeginDrawing();
    DrawText("Debug Mode", GetScreenWidth() - 100, GetScreenHeight() - 20, 10, BLACK);
    EndDrawing();
}