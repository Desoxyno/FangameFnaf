#include "springtrap.h"

void Springtrap::Update()
{
    maxDist = 3.0f * GetFrameTime();
    next_pos = path_points[current_point];
    if (current_pos == next_pos && (current_point + 1) < path_points.size())
    {
        next_pos = path_points[current_point += 1];
    }
    current_pos = Vector3MoveTowards(current_pos, next_pos, maxDist);
    positionM = current_pos;
};