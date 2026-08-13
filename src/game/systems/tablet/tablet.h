#pragma once

#include "engine/gameobject.hpp"

class Tablet : public GameObject
{
private:
    enum class State
    {
        Closed,
        Opening,
        Open,
        Closing
    };

    State state = State::Closed;

    RenderTexture2D screentexture{};

    R3D_AnimationPlayer anim_player;
    R3D_AnimationLib anim_lib;

    float anim_timer = 0.0f;

    Tablet(const Tablet&) = delete;
    Tablet& operator=(const Tablet&) = delete;

public:
    Tablet();
    void Exit() override;

    void Update() override;
    void Draw(PlayerCamera& camera) override;

    void Switch();
};