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

    float anim_timer = 0.0f;

    Tablet(const Tablet&) = delete;
    Tablet& operator=(const Tablet&) = delete;

public:
    Tablet();

    void Update() override;
    void Exit() override;

    void Switch();

    bool IsOpen() const;

    void ApplyShader(Shader* shader);
};