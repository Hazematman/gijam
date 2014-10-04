#include "iostream"
#include "player.hpp"
using namespace std;

Player::Player(){
	this->speed = 40;
	this->rb.pos = sf::Vector2f(0,200);
	this->isMovingLeft = false;
	this->isMovingRight = false;
}

void Player::update(float dt){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (!isMovingLeft) {
			isMovingLeft = true;
			rb.vel += sf::Vector2f(-speed,0.);
		}
	} else if (isMovingLeft) {
		isMovingLeft = false;
		if(rb.vel.x != 0)
			rb.vel -= sf::Vector2f(-speed,0.);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (!isMovingRight) {
			isMovingRight = true;
			rb.vel += sf::Vector2f(+speed,0.);
		}
	} else if (isMovingRight && rb.vel.x != 0) {
		isMovingRight = false;
		if(rb.vel.x != 0)
			rb.vel -= sf::Vector2f(+speed,0.);
	}
}

void Player::render(sf::RenderWindow &screen){
	sprite.setPosition(rb.pos);
	screen.draw(this->sprite);
}
