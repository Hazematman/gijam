#include "platform.hpp"
using namespace std;

Platform::Platform(){
	this->rb = RigidBody(10, 300, 100, 10);
	this->rb.moves = false;
	this->rb.tag = "platform";
}

void Platform::update(float dt){
}

void Platform::render(sf::RenderWindow &screen){
	sprite.setPosition(rb.pos);
	screen.draw(this->sprite);
}
