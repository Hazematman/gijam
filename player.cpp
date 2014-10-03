#include "player.hpp"

Player::Player(sf::Sprite, float x, float y){
	this->sprite = sprite;
	sf::Vector2u spriteSize = sprite.getTexture()->getSize();
	this->rb = RigidBody(x,y,spriteSize.x,spriteSize.y);
}

void Player::update(float dt){
}

void Player::render(){
}