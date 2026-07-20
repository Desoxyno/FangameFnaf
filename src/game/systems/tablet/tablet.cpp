#include "tablet.h"

Tablet::Tablet()
{
    name = "Tablet";

    scaleM = {0.5, 0.5, 0.5};
    positionM = {10.3f, 4.0f, -6.4f};
    rotationM = {0.0f, 0.0f, 0.0f};

    animations = nullptr;
    animationCount = 0;

    currentFrame = 0;
    anim_timer = 0.0f;
    animFrameSpeed = 0.02f;

    state = State::Closed;

    model = LoadModel("../assets/models/Office/camera_monitor.glb");

    animations = LoadModelAnimations("../assets/models/Office/camera_monitor.glb", &animationCount);

    if (animations == nullptr || animationCount == 0)
    {
        TraceLog(LOG_ERROR, "Tablet animation loading failed");
        return;
    }

    if (!IsModelAnimationValid(model, animations[0]))
    {
        TraceLog(LOG_ERROR, "Tablet animation incompatible with model");
    }

    TraceLog(LOG_INFO, "Tablet animation loaded (%d frames)", animations[0].keyframeCount);
}

Tablet::~Tablet()
{
    if (animations != nullptr && animationCount > 0)
    {
        UnloadModelAnimations(animations, animationCount);
    }

    UnloadModel(model);
}

void Tablet::Switch()
{
    if (state == State::Closed)
    {
        state = State::Opening;
    }
    if (state == State::Open)
    {
        state = State::Closing;
    }
}

void Tablet::Update()
{
    TraceLog(LOG_INFO, "State %d Frame %d", (int) state, currentFrame);

    if (animations == nullptr || animationCount == 0)
    {
        return;
    }

    ModelAnimation& animation = animations[0];

    if (state == State::Closed)
    {
        currentFrame = 0;
    }

    if (state == State::Open)
    {
        currentFrame = 34;
    }

    if (state == State::Opening || state == State::Closing)
    {
        anim_timer += GetFrameTime();

        if (anim_timer >= animFrameSpeed)
        {
            anim_timer = 0.0f;

            if (state == State::Opening)
            {
                currentFrame++;

                if (currentFrame >= animation.keyframeCount - 2)
                {
                    currentFrame = animation.keyframeCount - 2;
                    state = State::Open;
                }
            }
            else if (state == State::Closing)
            {
                currentFrame--;

                if (currentFrame <= 0)
                {
                    currentFrame = 0;
                    state = State::Closed;
                }
            }
        }
    }

    UpdateModelAnimation(model, animation, currentFrame);
}

void Tablet::Draw()
{
    DrawModelEx(model, positionM, rotationM, 0, scaleM, WHITE);
}

void Tablet::ApplyShader(Shader* shader)
{
    if (shader == nullptr)
    {
        return;
    }

    for (int i = 0; i < model.materialCount; i++)
    {
        model.materials[i].shader = *shader;
    }
}