#include "raylib.h"
#include <vector>
#include <iostream>

class Node {
private:
    std::mt19937 gen;
public:
	std::string name;
	Vector3 position;

	std::vector<Node*> neighbors_nodes;
	bool accessible;
	Node* search_next_node() {
		std::uniform_int_distribution<> dist(0, neighbors_nodes.size() - 1);
		return neighbors_nodes[dist(gen)];
	}

	void Log() const {
		std::cout << "Node(" << this->name << ")\nSes voisins sont :\n";
		for (Node* nodeN : neighbors_nodes) {
			if (nodeN != nullptr) {
				std::cout << " Neighbor Node(" << nodeN->name << ")\n";
			}
			
		} 
	}

	Node(std::string nameN, Vector3 pos) : gen(std::random_device{}()) {
		this->name = nameN;
		this->position = pos;
	}
	};