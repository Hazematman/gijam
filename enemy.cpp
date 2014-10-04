#include "enemy.hpp"
using namespace std;

Enemy::Enemy(){
	this->speed = 50;
	this->pos = sf::Vector2f(200,200);
	this->tag = "enemy";
	this->body = sf::Rect<float> (0,200,64,64);
	this->isMovingLeft = false;
	this->isMovingRight = false;
	this->facingLeft = false;
	this->sprite.setScale(2,2);
	this->attackCd = 0;

	this->currentFrame = 0;
	this->currentAnim = 0;
}

void Enemy::update(float dt){
	// Try to move towards the player, if we are too far
	if (abs(gplayer->pos.x - this->pos.x) >= 10) {
		if (gplayer->pos.x < this->pos.x) {
			if (!isMovingLeft) {
				isMovingLeft = true;
				vel += sf::Vector2f(-speed,0.);
			}
		} else if (isMovingLeft) {
			isMovingLeft = false;
			if(vel.x != 0)
				vel -= sf::Vector2f(-speed,0.);
		}
		if (gplayer->pos.x > this->pos.x) {
			if (!isMovingRight) {
				isMovingRight = true;
				vel += sf::Vector2f(+speed,0.);
			}
		} else if (isMovingRight) {
			isMovingRight = false;
			if(vel.x != 0)
				vel -= sf::Vector2f(+speed,0.);
		}
		if (this->attackCd <= 0 && isMovingLeft) {
			facingLeft = true;
			sprite.setScale(-2,2);
		} else if (this->attackCd <= 0 && isMovingRight) {
			facingLeft = false;
			sprite.setScale(+2,2);
		}
	} else if (this->attackCd <= 0) {
		// We are in attacking range

	}
}

void Enemy::render(sf::RenderWindow &screen){
	sprite.setTextureRect(sf::IntRect((int)currentFrame*32,(3+this->currentAnim)*32,32,32));
	sprite.setPosition(pos);
	if(facingLeft){
		sprite.move(64,0);
	}
	screen.draw(this->sprite);
	for (int i = 0; i < this->aliveAttacks.size(); i++) {
		Attack* thisAttack = aliveAttacks.at(i).get();
		thisAttack->pos = this->pos + (this->facingLeft ? sf::Vector2f(35,-4) : sf::Vector2f(-4,-4));
		thisAttack->render(screen);
	}
}

bool Enemy::onHit(int damage){
	this->dead = true;
	cout << "Ohhh noooo" << endl;
	return true;
};
