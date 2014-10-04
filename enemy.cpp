#include "enemy.hpp"
using namespace std;

enum anims{
	IDLE,
	WALK,
};

#define FRAMERATE 4
#define WFRAMERATE 6

Enemy::Enemy(){
	this->speed = 30;
	this->pos = sf::Vector2f(200,200);
	this->tag = "enemy";
	this->body = sf::Rect<float> (0,200,64,64);
	this->isMovingLeft = false;
	this->isMovingRight = false;
	this->facingLeft = false;
	this->sprite.setScale(2,2);
	this->attackCd = 0;

	this->currentFrame = 0;
	this->currentAnim = IDLE;

	this->sTex.loadFromFile("./data/images/attacksheet.png");
	this->sSpr.setTextureRect(sf::IntRect(0,4*32,32,32));
	this->sSpr.setTexture(this->sTex);
	this->sSpr.setScale(+2,2);
}

void Enemy::update(float dt){
	// Try to move towards the player, if we are too far
	if (abs(gplayer->pos.x - this->pos.x) >= 60) {
		//cout << "trying to move" << endl;
		if (gplayer->pos.x < this->pos.x) {
			isMovingLeft = true;
			currentAnim = WALK;
			vel += sf::Vector2f(-speed,0.);
		} else if (isMovingLeft) {
			isMovingLeft = false;
			currentAnim = IDLE;
			currentFrame = 0;
			vel -= sf::Vector2f(-speed,0.);
		}
		if (gplayer->pos.x > this->pos.x) {
			isMovingRight = true;
			currentAnim = WALK;
			vel += sf::Vector2f(+speed,0.);
		} else if (isMovingRight) {
			isMovingRight = false;
			currentAnim = IDLE;
			currentFrame = 0;
			vel -= sf::Vector2f(+speed,0.);
		}
		if (this->attackCd <= 0 && isMovingLeft) {
			facingLeft = true;
			sprite.setScale(-2,2);
			sSpr.setScale(-2,2);
		} else if (this->attackCd <= 0 && isMovingRight) {
			facingLeft = false;
			sprite.setScale(+2,2);
			sSpr.setScale(+2,2);
		}
	} else if (this->attackCd <= 0) {
		// Cancel current movement
		if (isMovingLeft) {
			isMovingLeft = false;
			if(vel.x != 0)
				vel -= sf::Vector2f(-speed,0.);
		}
		if (isMovingRight) {
			isMovingRight = false;
			if(vel.x != 0)
				vel -= sf::Vector2f(+speed,0.);
		}
		// We are in attacking range
		this->aliveAttacks.push_back(unique_ptr<Attack>(new AttackStab(10, STAB_CD, this->facingLeft, false)));
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
		currentFrame = fmod(currentFrame, 6);
	}
}

void Enemy::render(sf::RenderWindow &screen){
	if (!this->dead) {
		//cout << currentFrame << " " << currentAnim << endl;
		sprite.setTextureRect(sf::IntRect((int)currentFrame*32,(3+this->currentAnim)*32,32,32));
		sprite.setPosition(pos);
		if(facingLeft){
			sprite.move(64,0);
		}
		screen.draw(this->sprite);
		if(this->aliveAttacks.size() > 0){
			for (int i = 0; i < this->aliveAttacks.size(); i++) {
				sf::RectangleShape s;
				s.setSize(sf::Vector2f(64,64));
				Attack* thisAttack = aliveAttacks.at(i).get();
				thisAttack->pos = this->pos + (this->facingLeft ? sf::Vector2f(28,-4) : sf::Vector2f(36,-4));
				thisAttack->body.left = this->body.left + (this->facingLeft ? -28 : 36);
				thisAttack->body.top = this->body.top - 4;
				s.setPosition(thisAttack->body.left, thisAttack->body.top);
				//screen.draw(s);
				thisAttack->render(screen);
			}
		} else {
			sf::Vector2f pos = this->pos + (this->facingLeft ? sf::Vector2f(28,-4) : sf::Vector2f(36,-4));
			sSpr.setPosition(pos);
			if(currentAnim != IDLE){
				this->sSpr.setTextureRect(sf::IntRect(32,4*32,32,32));
			} else {
				this->sSpr.setTextureRect(sf::IntRect(0,4*32,32,32));
			}
			screen.draw(sSpr);
		}
	}
}

bool Enemy::onHit(int damage, bool facingLeft){
	/*this->dead = true;
	for (int i = 0; i < this->aliveAttacks.size(); i++) {
		Attack* thisAttack = aliveAttacks.at(i).get();
		thisAttack->dead = true;
		gworld->removeBody(thisAttack);
	}
	gworld->removeBody(this);*/
	vel.x += (facingLeft ? -10 : 10);
	return true;
};
