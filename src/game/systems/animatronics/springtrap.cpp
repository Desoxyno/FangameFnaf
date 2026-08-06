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

    

    basement = new Node("Basement", {-24, 0, 0});
    
    office_left = new Node("Office Left", {-3.5, 0, 0});
    office_front = new Node("Office Front", {1.7, 0, -2.4});

    basement->neighbors_nodes.push_back(office_left);
    basement->neighbors_nodes.push_back(office_front);

    office_front->neighbors_nodes.push_back(basement);
    office_left->neighbors_nodes.push_back(basement);

    previous_node = basement;
    current_node = basement;

    next_node = current_node->search_next_node();
};

Springtrap::~Springtrap() {
    delete basement;
    delete office_left;
    delete office_front;
};