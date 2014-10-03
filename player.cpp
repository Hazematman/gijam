#include "player.hpp"

Player::Player(){
	this->rb = RigidBody(0,0,0,0);
}

Player::Player(sf::Texture texture, float x, float y){
	sprite.setTexture(texture);
	this->texture = texture;
	sf::Vector2u spriteSize = sprite.getTexture()->getSize();
	this->rb = RigidBody(x,y,spriteSize.x,spriteSize.y);
}

void Player::update(float dt){
}

void Player::render(sf::RenderWindow &screen){
	screen.draw(this->sprite);
}
