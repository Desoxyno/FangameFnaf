#include "raylib.h"
#include <vector>

class Node {
private:
    std::mt19937 gen;
public:
	Vector3 position;
	std::vector<Node*> neighbors_nodes;
	bool accessible;
	Node* search_next_node() {
		std::uniform_int_distribution<> dist(0, neighbors_nodes.size() - 1);
		return neighbors_nodes[dist(gen)];
	}
	Node() : gen(std::random_device{}()) {}
	};