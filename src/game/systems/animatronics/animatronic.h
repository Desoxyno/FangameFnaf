#pragma once

#include "engine/gameobject.hpp"

class Animatronic : public GameObject
{
public:
    enum class PossibleRooms
    {
        MainStage
    };

    std::string name;

    PossibleRooms current_room = PossibleRooms::MainStage;

    int next_room = 0;
};