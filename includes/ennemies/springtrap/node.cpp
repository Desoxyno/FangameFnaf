#include "node.h"
#include "config/config.h"

#ifdef DEBUG_BUILD
    #include <iostream>
#endif

Node* Node::search_next_node() {
    std::span<Node*> neighbors = getNeighborsArray(*this);
    assert(neighbors.size() > 0);
    std::uniform_int_distribution<int> dist(0, neighbors.size() - 1);
	return neighbors[dist(gen)];
}

#ifdef DEBUG_BUILD
	void Node::Log() {
        std::span<Node*> neighbors = getNeighborsArray(*this);
		std::cout << "Node(" << this->name << ")\nSes voisins sont :\n";
		for (Node* nodeN : neighbors) {
			if (nodeN != nullptr) {
				std::cout << " Neighbor Node(" << nodeN->name << ")\n";
			}
			
		} 
	}
    void Node::LogPos() {
        std::cout << name << " X: " << position.x << " Y: " << position.y << " Z: " << position.z << std::endl;
    }
#endif

Node::Node(Node_Names name, Vector3 position) : name(name), position(position) {}