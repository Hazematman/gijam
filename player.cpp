#include "iostream"
#include "player.hpp"
using namespace std;

Player::Player(){
	this->speed = 50;
	this->pos = sf::Vector2f(0,200);
	this->tag = "player";
	this->body = sf::Rect<float> (0,200,32,64);
	this->isMovingLeft = false;
	this->isMovingRight = false;
	this->facingLeft = false;
	this->sprite.setScale(2,2);
	this->attackCd = 0;
}

void Player::update(float dt){
	// Horizontal Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (!isMovingLeft) {
			sprite.setScale(-2,2);
			isMovingLeft = true;
			facingLeft = true;
			vel += sf::Vector2f(-speed,0.);
		}
	} else if (isMovingLeft) {
		isMovingLeft = false;
		if(vel.x != 0)
			vel -= sf::Vector2f(-speed,0.);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (!isMovingRight) {
			sprite.setScale(2,2);
			isMovingRight = true;
			facingLeft = false;
			vel += sf::Vector2f(+speed,0.);
		}
	} else if (isMovingRight) {
		isMovingRight = false;
		if(vel.x != 0)
			vel -= sf::Vector2f(+speed,0.);
	}

	// Vertical Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->jumpPowerLeft > 0) {
		vel += sf::Vector2f(0.,-GRAVITY*this->jumpPowerLeft/MAX_JUMP*dt*40);
		this->jumpPowerLeft -= dt*10;
	} else {
		this->jumpPowerLeft = 0;
	}
	if (vel.y == 0 && collided.size() > 0) {
		this->jumpPowerLeft = MAX_JUMP;
	}

	// Attacks
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && this->attackCd <= 0) {
		cout << "Attack" << endl;
		this->aliveAttacks.push_back(unique_ptr<Attack>(new AttackStab(10,200, this->facingLeft)));
		AttackStab *newstab = ((AttackStab*) this->aliveAttacks.back().get());
		newstab->pos = this->pos + (this->facingLeft ? sf::Vector2f(28,4) : sf::Vector2f(4,4));
		newstab->tag = "attack";
		newstab->body = sf::Rect<float> (0,200,32,32);
		newstab->setSprite("./data/images/attacksheet.png");
		gworld->bodies.push_back(newstab);
		this->attackCd = STAB_CD;
	}
	this->attackCd -= dt;

	for (int i = 0; i < this->aliveAttacks.size(); i++) {
		Attack *thisAttack = aliveAttacks.at(i).get();
		if (thisAttack->dead) {
			this->aliveAttacks.erase(this->aliveAttacks.begin() + i);
			i--;
			continue;
		}

		cout << "atk" << endl;
		thisAttack->update(dt);
	}
}

void Player::render(sf::RenderWindow &screen){
	sprite.setTextureRect(sf::IntRect(0,0,16,32));
	sprite.setPosition(pos);
	if(facingLeft){
		sprite.move(32,0);
	}
	screen.draw(this->sprite);
	for (int i = 0; i < this->aliveAttacks.size(); i++) {
		Attack* thisAttack = aliveAttacks.at(i).get();
		thisAttack->render(screen);
	}
}
