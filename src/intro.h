#pragma once

#include "camera.hpp"
#include "gameobject.hpp"
#include "scene.hpp"

class Intro : public Scene
{
  private:
    Light lights[1];
    GameObject hallway;
    PlayerCamera camera;
    double introStartTime;

  public:
    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;
};