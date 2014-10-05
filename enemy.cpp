#include "enemy.hpp"
using namespace std;

enum anims{
	IDLE,
	WALK,
	HURT
};

#define FRAMERATE 4
#define WFRAMERATE 6

Enemy::Enemy(){
	this->speed = 20;
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
	this->attackToUse = rand() % 3;
}

void Enemy::update(float dt){
	// Try to move towards the player, if we are too far
	if (abs((gplayer->pos.x+gplayer->body.width/2) - (pos.x+body.width/2)) >= 60 && invulnWindow <= 0) {
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
			if(vel.x != 0 && invulnWindow <= 0)
				vel -= sf::Vector2f(-speed,0.);
		}
		if (isMovingRight) {
			isMovingRight = false;
			if(vel.x != 0 && invulnWindow <= 0)
				vel -= sf::Vector2f(+speed,0.);
		}
		// We are in attacking range
		if (attackToUse == 0) {
			this->aliveAttacks.push_back(unique_ptr<Attack>(new AttackStab(10, STAB_CD-0.3, facingLeft, false)));
		} else if (attackToUse == 1) {
			this->aliveAttacks.push_back(unique_ptr<Attack>(new AttackSlash(10, STAB_CD-0.3, facingLeft, false)));
		} else {
			this->aliveAttacks.push_back(unique_ptr<Attack>(new AttackSwipe(10, STAB_CD-0.3, facingLeft, false)));
		}
		Attack *newstab = this->aliveAttacks.back().get();
		//newstab->pos = this->pos + (this->facingLeft ? sf::Vector2f(35,-4) : sf::Vector2f(-4,-4));
		newstab->tag = "attack";
		newstab->parent = this;
		newstab->body = sf::Rect<float> (0,200,64,50);
		newstab->setSprite("./data/images/attacksheet.png");
		gworld->bodies.push_back(newstab);
		this->attackCd = STAB_CD;
		int soundToPlay = rand() % 3;
		if (soundToPlay == 0) {
			stabSnd.play();
		} else if (soundToPlay == 1) {
			slashSnd.play();
		} else {
			atkSnd.play();
		}
	}
	this->attackCd -= dt;

	for (int i = 0; i < collided.size(); i++) {
		Entity* collidedEnt = (Entity*) collided.at(i);
		if (collidedEnt->tag == "platform") {
			this->jumpPowerLeft = MAX_JUMP;
			continue;
		}
		// Jump onto people, pushing them away
		if (collidedEnt->moves && collidedEnt->pos.y > pos.y+body.height && collidedEnt->invulnWindow <= 0) {
			collidedEnt->invulnWindow = INVULN_WINDOW;
			collidedEnt->vel.x = (pos.x < collidedEnt->pos.x ? 20 : -20);
			cout << "EnemyJump" << vel.x << endl;
		}
		if (invulnWindow-dt <= 0) {
			invulnWindow += dt;
		}
	}
	invulnWindow -= dt;

	for (int i = 0; i < this->aliveAttacks.size(); i++) {
		Attack *thisAttack = aliveAttacks.at(i).get();
		if (thisAttack->dead || invulnWindow > 0) {
			gworld->removeBody(thisAttack);
			this->aliveAttacks.erase(this->aliveAttacks.begin() + i);
			i--;
			continue;
		}

		thisAttack->update(dt);
	}

	if (invulnWindow > 0 && currentAnim != HURT) {
		currentAnim = HURT;
		currentFrame = 0;
	}

	if (this->currentAnim == IDLE){
		currentFrame += FRAMERATE*dt;	
		currentFrame = fmod(currentFrame, 2);
	} else if(this->currentAnim == WALK){
		currentFrame += WFRAMERATE*dt;
		currentFrame = fmod(currentFrame, 6);
	} else if(this->currentAnim == HURT){
		currentFrame = 0;
	}

	// Fall off? DED
	if (pos.y > 486) {
		dead = true;
		for (int i = 0; i < this->aliveAttacks.size(); i++) {
			Attack* thisAttack = aliveAttacks.at(i).get();
			thisAttack->dead = true;
			gworld->removeBody(thisAttack);
		}
		gworld->removeBody(this);
	}
}

void Enemy::render(sf::RenderWindow &screen){
	if (!dead) {
		//cout << currentFrame << " " << currentAnim << endl;
		sprite.setTextureRect(sf::IntRect((int)currentFrame*32,(5+this->currentAnim)*32,32,32));
		sprite.setPosition(pos);
		if(facingLeft){
			sprite.move(64,0);
		}
		sf::RectangleShape rect(sf::Vector2f(body.width,body.height));
		rect.setPosition(body.left,body.top);
		//screen.draw(rect);
		screen.draw(this->sprite);
		if(this->aliveAttacks.size() > 0){
			for (int i = 0; i < this->aliveAttacks.size(); i++) {
				sf::RectangleShape s;
				s.setSize(sf::Vector2f(32,32));
				Attack* thisAttack = aliveAttacks.at(i).get();
				thisAttack->pos = this->pos + (this->facingLeft ? sf::Vector2f(28,-4) : sf::Vector2f(36,-4));
				thisAttack->body.left = this->body.left + (this->facingLeft ? 28 : 36);
				thisAttack->body.top = this->body.top + 6;
				s.setPosition(thisAttack->body.left, thisAttack->body.top);
				if(facingLeft){
					thisAttack->body.width = -(54);
				} else {
					thisAttack->body.width = 64; 
				}
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
	vel.x = (facingLeft ? -150 : 150);
	return true;
};
