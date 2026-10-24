#pragma once

#include "raylib.h"
#include <cassert>
#include <random>

#include "global_variables.h"

inline std::random_device rd; 
inline std::mt19937 gen(rd());

class Node {
public:
	Node_Names name;
	Vector3 position;

	bool accessible;

    Node(Node_Names name, Vector3 position);
    Node* search_next_node();
    void Log();
    void LogPos();
};

