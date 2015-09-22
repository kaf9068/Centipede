#include "GameObject.h"

GameObject::GameObject(Shape* shapePtr, vec3 position, float mass, vec3 velocity, float scale, vec3 rotationAxis, float rotationAmount, float angularVelocity, vec3 color)
{
	this->shapePtr = shapePtr;
	this->position = position;
	this->mass = mass;
	this->velocity = velocity;
	this->scale = scale;
	this->rotationAxis = rotationAxis;
	this->rotationAmount = rotationAmount;
	this->angularVelocity = angularVelocity;
	this->color = color;
	this->force = vec3(0, 0, 0);

	this->collisionRadius = 0.2f;

	this->visible = false;
	this->atRest = false;
}

void GameObject::update(float dt)
{

	vec3 drag = velocity * -0.10f;
	this->addForce(drag);

	vec3 gravity = vec3(0, mass * -0.1f, 0);
	this->addForce(gravity);

	rotationAmount += angularVelocity * dt;
	velocity += force	 * dt / mass;

	if (position.x - collisionRadius < -1.0f || position.x + collisionRadius > 1.0f) {
		velocity.x *= -1;
	}

	if (position.y - collisionRadius < -1.0f || position.y + collisionRadius > 1.0f) {
		velocity.y *= -1;
	}


	position += velocity * dt;
	force = vec3(0, 0, 0);
}

void GameObject::draw()
{
	shapePtr->draw(position, vec3(scale, scale, scale), rotationAxis, rotationAmount, color);
}

float GameObject::getScale()
{
	return scale;
}

float GameObject::getMass()
{
	return mass;
}

void GameObject::setVelocity(vec3 velocity)
{
	this->velocity = velocity;
}

vec3 GameObject::getVelocity()
{
	return velocity;
}

void GameObject::addForce(vec3 force)
{
	this->force += force;
}

void GameObject::setPosition(vec3 position)
{
	this->position = position;
}

vec3 GameObject::getPosition()
{
	return this->position;
}

GameObject::GameObject(void)
{
}


GameObject::~GameObject(void)
{
}

void GameObject::setVisible(bool visible) {
	this->visible = visible;
}

bool GameObject::isVisible() {
	return this->visible;
}

void GameObject::setAtRest(bool rest) {
	this->atRest = rest;
}

bool GameObject::isAtRest() {
	return this->atRest;
}