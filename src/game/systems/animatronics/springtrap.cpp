#include "springtrap.h"

void Springtrap::UpdatePosition()
{
    maxDist = 5.0f * GetFrameTime();
    Vector3MoveTowards(current_pos, next_pos, maxDist);
};