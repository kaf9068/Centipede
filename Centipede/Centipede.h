#pragma once

#include "GameObject.h"

#include <glm\glm.hpp>
#include <vector>
using namespace glm;
using namespace std;

#define MAX_LENGTH 25

enum BodyType {
	HEAD,
	BODY
};

struct Node {
	BodyType type;
	Node* next;
	vec2 position;
};

class Centipede : public GameObject {

public:

	Centipede();
	~Centipede();

	void init();
	void update();
	void draw();



private:

	size_t length;
	vector<Node> nodes;

};