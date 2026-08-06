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

    maxDist = 3.0f * GetFrameTime();

    if (current_node->position == next_node->position )
    {
        next_node = current_node->search_next_node();

        if (timer == 0) {
            std::cout << "\nChangement de node\n";
        }
        
    }
    positionM = Vector3MoveTowards(current_node->position, next_node->position, maxDist);

    if (timer == 0) {
    std::cout << "Springtrap bouge\n";
    }
};

void Springtrap::Log() {
    current_node->Log();
};

Springtrap::Springtrap() {
    

    basement = new Node("Basement", {0, 0, 0});
    
    office_left = new Node("Office Left", {10, 10, 10});
    office_front = new Node("Office Front", {-10, -10, -10});

    basement->neighbors_nodes.push_back(office_left);
    basement->neighbors_nodes.push_back(office_front);

    current_node = basement;

    next_node = current_node->search_next_node();
};

Springtrap::~Springtrap() {
    delete basement;
    delete office_left;
    delete office_front;
};