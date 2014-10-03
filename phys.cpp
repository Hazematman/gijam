#include "phys.hpp"
using namespace std;

RigidBody::RigidBody(float x, float y, float dx, float dy){
	this->body = sf::Rect<float>(x, y, dx, dy);
	moves = true;
}

void PhysWorld::update(float dt){
	for(RigidBody* body : bodies){
		body->pos += body->vel*dt;
	}
}
