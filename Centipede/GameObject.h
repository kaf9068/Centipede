#pragma once
#include "Shape.h"
#include <glm\glm.hpp>
using namespace glm;

class GameObject
{
public:
	float getScale();
	void update(float dt);
	void draw();
	void addForce(vec3 force);
	float getMass();
	void setVelocity(vec3 velocity);
	vec3 getVelocity();
	void setPosition(vec3 position);
	vec3 getPosition();
	GameObject(Shape* shapePtr, vec3 position, float mass, vec3 velocity, float scale, vec3 rotationAxis, float rotationAmount, float angularVelocity, vec3 color);

	void setVisible(bool visible);
	bool isVisible();

	void setAtRest(bool rest);
	bool isAtRest();

	~GameObject(void);

private:
	Shape* shapePtr;
	vec3 position;
	float mass;
	vec3 velocity;
	float scale;
	vec3 rotationAxis;
	float rotationAmount;
	float angularVelocity;
	vec3 force;
	vec3 color;

	float collisionRadius;

	bool visible;
	bool atRest;

	GameObject(void);
};

