#include "iostream"
#include "player.hpp"
using namespace std;

Player::Player(){
	this->rb = RigidBody(0,0,0,0);
}

void Player::setSprite(string filename){
	texture.loadFromFile(filename);
	sprite.setTexture(texture);
	sf::Vector2u spriteSize = sprite.getTexture()->getSize();
	this->rb = RigidBody(rb.pos.x,rb.pos.y,spriteSize.x,spriteSize.y);
}

void Player::update(float dt){
}

void Player::render(sf::RenderWindow &screen){
	screen.draw(this->sprite);
}
