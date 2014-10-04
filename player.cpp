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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (!isMovingLeft) {
			isMovingLeft = true;
			rb.vel += sf::Vector2f(-10.,0.);
		}
	} else if (isMovingLeft) {
		isMovingLeft = false;
		rb.vel -= sf::Vector2f(-10.,0.);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (!isMovingRight) {
			isMovingRight = true;
			rb.vel += sf::Vector2f(+10.,0.);
		}
	} else if (isMovingRight) {
		isMovingRight = false;
		rb.vel -= sf::Vector2f(+10.,0.);
	}
}

void Player::render(sf::RenderWindow &screen){
	sprite.setPosition(rb.pos);
	screen.draw(this->sprite);
}
