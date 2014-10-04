#include "platform.hpp"
using namespace std;

Platform::Platform(){
	this->rb = RigidBody(10, 300, 100, 10);
	this->rb.moves = false;
}

void Platform::setSprite(string filename){
	texture.loadFromFile(filename);
	sprite.setTexture(texture);
	sf::Vector2u spriteSize = sprite.getTexture()->getSize();
	this->rb = RigidBody(rb.pos.x,rb.pos.y,spriteSize.x,spriteSize.y);
	this->rb.moves = false;
}

void Platform::update(float dt){
}

void Platform::render(sf::RenderWindow &screen){
	sprite.setPosition(rb.pos);
	screen.draw(this->sprite);
}
