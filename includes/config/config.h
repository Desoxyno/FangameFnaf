#pragma once

#include "ennemies/springtrap/node.h"
#include "global_variables.h"
#include <span>

inline Node nodes[6] = {{Basement, {-24, 1, 0.3}},
                        {OfficeLeft, {-3.5, 1, 0.3}},
                        {OfficeFront, {1.7, 1, -2.4}},
                        {HallwayEmployees, {-21, 1, 0.3}},
                        {HallwayService, {-10, 1, 0.3}},
                        {PartsService, {-10, 1, -6}}
};

inline Node* basement_neighbors[1] = {&nodes[3]};
inline Node* officeL_neighbors[1] = {&nodes[4]};
// inline Node* officeF_neighbors[1] = {}; Empty for now
inline Node* hallwayE_neighbors[2] = {&nodes[0], &nodes[4]};
inline Node* hallwayS_neighbors[2] = {&nodes[3], &nodes[1]};
inline Node* parts_neighbors[1] = {&nodes[4]};

inline Node* empty[1] = {};

inline std::span<Node*> getNeighborsArray(Node &node) {
    switch (node.name) {
        case Basement:
            return basement_neighbors;
        case OfficeLeft:
            return officeL_neighbors;
        case OfficeFront: // Aucun voisins pour le moment
             return empty;
        case HallwayEmployees:
            return hallwayE_neighbors;
        case HallwayService:
            return hallwayS_neighbors;
        case PartsService:
            return parts_neighbors;
        default:
            return empty;
            
    }
    
}

inline Camera camera_mainmenu = {{1.77f, 2.3f, 2.0f}, {-1.0f, 0.85f, -4.2f}, {0.0f, 1.0f, 0.0f}, 45.0f, CAMERA_PERSPECTIVE};
inline Camera camera_night1 = {{-0.6f, 1.4f, -0.41f}, {5.4f, -10.6f, -1000.0f}, {0.0f, 1.0f, 0.0f}, 45.0f, CAMERA_PERSPECTIVE};