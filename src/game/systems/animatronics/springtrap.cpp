#include "springtrap.h"

void Springtrap::Update()
{
    maxDist = 3.0f * GetFrameTime();


    if (current_node->position == next_node->position)
    {
        next_node = current_node->search_next_node();
    }
    positionM = Vector3MoveTowards(current_node->position, next_node->position, maxDist);
};

Springtrap::Springtrap() {
    Node basement;
    Node office_left;
    Node office_front;
};