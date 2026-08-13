#include "tablet.h"

Tablet::Tablet()
{
    name = "Tablet";

    scaleM = {1, 1, 1};
    positionM = {0.64f, -1.2f, 0.45f};
    rotationM = {-180.0f, -90.0f, 0.0f};

    animations = nullptr;
    animationCount = 0;

    currentFrame = 0;
    anim_timer = 0.0f;
    animFrameSpeed = 0.001f;

    state = State::Closed;

    model = R3D_LoadModel("../assets/models/Office/camera_monitor.glb");

    anim_lib = R3D_LoadAnimationLib("../assets/models/Office/camera_monitor.glb");

    anim_player = R3D_LoadAnimationPlayer(model.skeleton, anim_lib);

    CalculatePivot();

    if (animations == nullptr || animationCount == 0)
    {
        TraceLog(LOG_ERROR, "Tablet animation loading failed");
        return;
    }
}

void Tablet::Exit()
{
    R3D_UnloadAnimationPlayer(anim_player);
    R3D_UnloadAnimationLib(anim_lib);
    R3D_UnloadModel(model, true);
}

void Tablet::Switch()
{
    if (state == State::Closed)
    {
        state = State::Opening;

        R3D_SetAnimationTime(&anim_player, 0, 0.0f);
        R3D_SetAnimationSpeed(&anim_player, 0, 1.0f);
        R3D_PlayAnimation(&anim_player, 0);
    }
    else if (state == State::Open)
    {
        state = State::Closing;

        R3D_SetAnimationSpeed(&anim_player, 0, -1.0f);
        R3D_PlayAnimation(&anim_player, 0);
    }
}

void Tablet::Update()
{
    R3D_UpdateAnimationPlayer(&anim_player, GetFrameTime());
}

void Tablet::Draw(PlayerCamera& camera)
{
    R3D_DrawAnimatedModelPro(model, anim_player, GetTransform());
}