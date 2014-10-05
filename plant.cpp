#include "plant.hpp"

#define FRAMERATE 6

void Plant::init(){
	this->texture.loadFromFile("./data/images/flytrap.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0,0,32,32));
	this->sprite.setScale(2,2);
}

void Plant::update(float dt){
	currentFrame += FRAMERATE*dt;
	currentFrame = fmod(currentFrame,4);
}

void Plant::render(sf::RenderWindow &screen){
	sprite.setPosition(pos);
	sprite.setTextureRect(sf::IntRect((int)currentFrame*32,0,32,32));
	screen.draw(sprite);
}
