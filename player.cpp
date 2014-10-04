#include "iostream"
#include "player.hpp"
using namespace std;

Player::Player(){
	this->speed = 50;
	this->rb.pos = sf::Vector2f(0,200);
	this->rb.tag = "player";
	this->isMovingLeft = false;
	this->isMovingRight = false;
}

void Player::update(float dt){
	// Horizontal Movement
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
	} else if (isMovingRight) {
		isMovingRight = false;
		if(rb.vel.x != 0)
			rb.vel -= sf::Vector2f(+speed,0.);
	}

	// Vertical Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->jumpPowerLeft > 0) {
		rb.vel += sf::Vector2f(0.,-GRAVITY*this->jumpPowerLeft/MAX_JUMP*dt*30);
		this->jumpPowerLeft -= dt*10;
	} else {
		this->jumpPowerLeft = 0;
	}
	if (rb.vel.y == 0 && rb.collided.size() > 0) {
		this->jumpPowerLeft = MAX_JUMP;
	}
}

void Player::render(sf::RenderWindow &screen){
	sprite.setPosition(rb.pos);
	screen.draw(this->sprite);
}
