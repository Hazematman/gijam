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
	/*for(RigidBody* body : bodies){
		if(body->moves){
			body->vel += gravity*dt;
			body->vel.x *= DRAG*(1-dt);
			body->pos += body->vel*dt;
			body->body.left = body->pos.x;
			body->body.top = body->pos.y;
		}
	}*/
	for(int i = 0; i < bodies.size(); i++){
		RigidBody* b1 = bodies.at(i);
		if (b1->dead) {
			bodies.erase(bodies.begin() + i);
			i==0 ? i=0: i--;
			continue;
		}
		b1->collided.clear();
		if(b1->moves){
			b1->vel += gravity*dt;
			b1->vel.x *= DRAG*(1-dt);
			b1->pos += b1->vel*dt;
			b1->body.left = b1->pos.x;
			b1->body.top = b1->pos.y;
		}
		for(RigidBody* b2 : bodies){
			if (b2->tag == "attack") {
				continue;
			}
			if(b1 != b2 && b1->body.intersects(b2->body)){
				b1->collided.push_back(b2);
				b2->collided.push_back(b1);
				b1->pos += b1->vel*-dt;
				b1->body.left = b1->pos.x;
				b1->body.top = b1->pos.y;
				sf::Rect<float> x = b1->body;
				sf::Rect<float> y = b1->body;
				x.left += b1->vel.x*dt;
				y.top += b1->vel.y*dt;
			   	if(x.intersects(b2->body)){
					b1->vel.x = 0;
				}	
				if(y.intersects(b2->body)){
					b1->vel.y = 0;
				}
				b1->pos += b1->vel*dt;
				b1->body.left = b1->pos.x;
				b1->body.top = b1->pos.y;
			}
		}
	}
}

void PhysWorld::removeBody(RigidBody* body) {
	for(int i = 0; i < bodies.size(); i++){
		if (body == bodies.at(i)) {
			bodies.erase(bodies.begin() + i);
			i==0 ? i=0: i--;
			continue;
		}
	}
}