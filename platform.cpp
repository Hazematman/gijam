#include "platform.hpp"
using namespace std;

Platform::Platform(){
	//this->rb = RigidBody(10, 300, 100, 10);
	this->pos = sf::Vector2f(10,300);
	this->moves = false;
	this->tag = "platform";
}

void Platform::update(float dt){
}

void Platform::render(sf::RenderWindow &screen){
	sprite.setPosition(pos);
	screen.draw(this->sprite);
}
