#pragma once
#ifndef AI_NODE_H
#define AI_NODE_H
#include<vector>
#include<stdlib.h>
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "CollideBaseGroup.h"
class Node;
#include "NodeDrawGroup.h"
class Node {
	private:
		std::vector<Node*> attached;
		Point position;
		bool drawnThisFrame;
	public:
		Node(Point position); // This is the constructor for a "null node" aka one that needs to be re-evaluated later
		Node(Point position, NodeDrawGroup& group, CollideBaseGroup& collision);
		~Node();
		Node* randomConnectedNode();
		Point getPosition();
		void draw();
		void reset();
		void addAttached(Node* node);
		static bool checkLocationValidity(Point position, CollideBaseGroup& collision);
};
#endif