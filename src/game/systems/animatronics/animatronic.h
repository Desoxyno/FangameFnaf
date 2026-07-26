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

    std::string icon;
};