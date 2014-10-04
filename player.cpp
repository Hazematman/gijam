#include "iostream"
#include "player.hpp"
using namespace std;

#define FRAMERATE 6
#define WFRAMERATE 8
#define KFRAMERATE 10

#define UPSPEED 30

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
	this->HP = 40;

	this->currentFrame = 0;
	this->currentAnim = 0;
}

void Player::update(float dt){
	// Horizontal Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (!isMovingLeft) {
			isMovingLeft = true;
			vel += sf::Vector2f(-speed,0.);
			currentAnim = WALK;
			currentFrame = 0;
		}
	} else if (isMovingLeft) {
		isMovingLeft = false;
		if(vel.x != 0) {
			vel -= sf::Vector2f(-speed,0.);
			if(currentAnim == KWALK)
				vel -= sf::Vector2f(-UPSPEED, 0);
		}
		currentAnim = IDLE;
		currentFrame = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (!isMovingRight) {
			isMovingRight = true;
			currentAnim = WALK;
			currentFrame = 0;
			vel += sf::Vector2f(+speed,0.);
		}
	} else if (isMovingRight) {
		isMovingRight = false;
		if(vel.x != 0) {
			vel -= sf::Vector2f(+speed,0.);
			if(currentAnim == KWALK)
				vel -= sf::Vector2f(UPSPEED,0);
		}
		currentAnim = IDLE;
		currentFrame = 0;
	}
	if (this->attackCd <= 0 && isMovingLeft) {
		facingLeft = true;
		sprite.setScale(-2,2);
	} else if (this->attackCd <= 0 && isMovingRight) {
		facingLeft = false;
		sprite.setScale(+2,2);
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
		this->aliveAttacks.push_back(unique_ptr<Attack>(new AttackStab(10, STAB_CD, this->facingLeft, true)));
		AttackStab *newstab = ((AttackStab*) this->aliveAttacks.back().get());
		//newstab->pos = this->pos + (this->facingLeft ? sf::Vector2f(35,-4) : sf::Vector2f(-4,-4));
		newstab->tag = "attack";
		newstab->body = sf::Rect<float> (0,200,64,64);
		newstab->setSprite("./data/images/attacksheet.png");
		gworld->bodies.push_back(newstab);
		this->attackCd = STAB_CD;
	}
	this->attackCd -= dt;

	for (int i = 0; i < this->aliveAttacks.size(); i++) {
		Attack *thisAttack = aliveAttacks.at(i).get();
		if (thisAttack->dead) {
			gworld->removeBody(thisAttack);
			this->aliveAttacks.erase(this->aliveAttacks.begin() + i);
			i--;
			continue;
		}

		thisAttack->update(dt);
	}

	if(this->currentAnim == IDLE){
		currentFrame += FRAMERATE*dt;	
		currentFrame = fmod(currentFrame, 2);
	} else if(this->currentAnim == WALK){
		currentFrame += WFRAMERATE*dt;
		if(currentFrame > 3){
			currentAnim = KWALK;
			this->vel += sf::Vector2f(isMovingLeft? -UPSPEED : UPSPEED ,0);
		}
		currentFrame = fmod(currentFrame, 3);
	} else if(this->currentAnim == KWALK){
		currentFrame += KFRAMERATE*dt;
		currentFrame = fmod(currentFrame, 3);
	}
}

void Player::render(sf::RenderWindow &screen){
	sprite.setTextureRect(sf::IntRect((int)this->currentFrame*16,(int)this->currentAnim*32,16,32));
	sprite.setPosition(pos);
	if(facingLeft){
		sprite.move(32,0);
	}
	screen.draw(this->sprite);
	for (int i = 0; i < this->aliveAttacks.size(); i++) {
		Attack* thisAttack = aliveAttacks.at(i).get();
		thisAttack->pos = this->pos + (this->facingLeft ? sf::Vector2f(35,-4) : sf::Vector2f(-4,-4));
		thisAttack->body.left = this->body.left + (this->facingLeft ? 35 : -4);
		thisAttack->body.top = this->body.top - 4;
		thisAttack->render(screen);
	}
}

bool Player::onHit(int damage){
	this->HP -= damage;
	cout << "Player hit" << endl;
	if (HP <= 0) {
		for (int i = 0; i < this->aliveAttacks.size(); i++) {
			Attack* thisAttack = aliveAttacks.at(i).get();
			thisAttack->dead = true;
		}
	}
	return true;
}
