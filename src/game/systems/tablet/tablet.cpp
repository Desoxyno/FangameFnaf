#include "tablet.h"

Tablet::Tablet()
{
    animations = nullptr;
    animationCount = 0;
    current_anim_frame = 0;

    model = LoadModel("../assets/models/Office/camera_monitor.glb");

    animations = LoadModelAnimations("../assets/models/Office/camera_monitor.glb", &animationCount);

    if (animations == nullptr || animationCount == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load animations!");
        return;
    }

    if (!animationCount > 0)
    {
        TraceLog(LOG_ERROR, "Aucune Animation");
    }

    TraceLog(LOG_INFO, "Loaded %d animation(s)", animationCount);

    if (!IsModelAnimationValid(model, animations[0]))
    {
        TraceLog(LOG_ERROR, "Animation incompatible avec le modele");
    }
}

Tablet::~Tablet()
{
    // if (animations != nullptr)
    // {
    //     UnloadModelAnimations(animations, animationCount);
    // }

    UnloadModel(model);
}

void Tablet::Switch()
{
    switch (state)
    {
        case State::Closed:
            state = State::Opening;
            break;

        case State::Open:
            state = State::Closing;
            break;

        default:
            break;
    }
}

void Tablet::Update()
{
    if (animationCount == 0 || animations == nullptr)
    {
        return;
    }

    ModelAnimation& animation = animations[0];

    anim_timer += GetFrameTime();

    if (anim_timer >= anim_speed)
    {
        anim_timer = 0.0f;

        if (state == State::Opening)
        {
            current_anim_frame++;

            if (current_anim_frame >= animation.keyframeCount)
            {
                current_anim_frame = animation.keyframeCount - 1;
                state = State::Open;
            }
        }
        else if (state == State::Closing)
        {
            current_anim_frame--;

            if (current_anim_frame <= 0)
            {
                current_anim_frame = 0;
                state = State::Closed;
            }
        }
    }

    UpdateModelAnimation(model, animation, current_anim_frame);

    TraceLog(LOG_INFO, "Frame %d / %d", current_anim_frame, animation.keyframeCount);
}

void Tablet::Draw()
{
    Matrix transform = GetTransform();

    for (int i = 0; i < model.meshCount; i++)
    {
        DrawMesh(model.meshes[i], model.materials[model.meshMaterial[i]], transform);
    }
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