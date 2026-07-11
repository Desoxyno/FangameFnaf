#pragma once

#include "camera.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include <vector>

class Intro : public Scene
{
  private:
    std::vector<Sound> sounds;
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