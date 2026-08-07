#include "springtrap.h"

void Springtrap::Update()
{

    // Log Function
    static float timer = 0;

    timer += GetFrameTime();

    if (timer >= 1.0f) {
        this->Log();
        timer = 0.0f;

    }

    if (positionM == next_node->position)
    {
        previous_node = current_node;
        current_node = next_node;
        next_node = previous_node->search_next_node();
        positionM = current_node->position;

        if (timer == 0) {
            std::cout << "\nChangement de node\n";
        }
        
    }
    positionM = Vector3MoveTowards(positionM, next_node->position, speed * GetFrameTime());

    if (timer == 0) {
    std::cout << "Springtrap bouge\n";
    }
};

void Springtrap::Log() {
    current_node->LogPos();
    LogPos();
    next_node->LogPos();
    current_node->Log();

};

Springtrap::Springtrap() {

    Basement_Entrance = new Node("Basement", {-24, 0, 0});
    
    Office_Left = new Node("Office Left", {-3.5, 0, 0});
    Office_Front = new Node("Office Front", {1.7, 0, -2.4});

    Hallway_Employees = new Node("Hallway Employees", {-21, 0, 0.3});
    Hallway_Service = new Node("Hallway Service", {-10, 0, 0.3});

    Basement_Entrance->AddNeighbors({Hallway_Employees});

    Hallway_Employees->AddNeighbors({Basement_Entrance, Hallway_Service});

    Hallway_Service->AddNeighbors({Hallway_Employees, Office_Left});

    Office_Left->AddNeighbors({Hallway_Service});

    previous_node = Basement_Entrance;
    current_node = Basement_Entrance;

    next_node = current_node->search_next_node();

    positionM = Basement_Entrance->position;
};

Springtrap::~Springtrap() {
    delete Basement_Entrance;
    delete Office_Left;
    delete Office_Front;
    delete Hallway_Employees;
    delete Hallway_Service;
};