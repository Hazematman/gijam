#include "phys.hpp"
using namespace std;

RigidBody::RigidBody(float x, float y, float dx, float dy){
	this->body = sf::Rect<float>(x, y, dx, dy);
	this->pos = sf::Vector2f(x,y);
	moves = true;
}

RigidBody::RigidBody(){
	this->body = sf::Rect<float>(0, 0, 0, 0);
	moves = true;
}

void PhysWorld::update(float dt){
	for(RigidBody* body : bodies){
		if(body->moves){
			body->vel += gravity*dt;
			body->pos += body->vel*dt;
		}
	}
	for(RigidBody* b1 : bodies){
		for(RigidBody* b2 : bodies){
			if(b1 != b2 && b1->body.intersects(b2->body)){
				b1->pos += b1->vel*-dt;
			}
		}
	}
}
