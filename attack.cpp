#include "attack.hpp"
using namespace std;

Attack::Attack() {
	this->frameNum = 0;
	this->framePos = 1;
	parent = NULL;
	this->damage = 0;
	this->lifetime = 10;
	this->tag = "attack";
	this->sprite.setScale(2,2);
	this->body = sf::Rect<float> (0,200,32,32);
	this->facingLeft = false;
	this->moves = false;
	this->fromPlayer = false;
	this->vel = sf::Vector2f(0,0);
	this->timeToNextFrame = 1;
	this->maxTimeToNextFrame = 1;
	attackType = 0;
}

void Attack::render(sf::RenderWindow &screen) {
	sf::RectangleShape rect(sf::Vector2f(body.width,body.height));
	rect.setPosition(body.left,body.top);
	//screen.draw(rect);
	sprite.setPosition(pos);
	sprite.setTextureRect(sf::IntRect(32*this->frameNum,framePos*32,32,32));
	screen.draw(this->sprite);
}

void Attack::update(float dt) {
	if (!this->dead) {
		for (RigidBody* collidedRB : this->collided) {
			Entity* collidedEnt = (Entity*) collidedRB;
			if (this->fromPlayer && collidedEnt->tag == "enemy") collidedEnt->onHit(damage, facingLeft);
			if (!(this->fromPlayer) && collidedEnt->tag == "player") collidedEnt->onHit(damage, facingLeft);
			if (collidedEnt->tag == "attack") {
				Attack* collidedAtk = (Attack*) collidedEnt;
				if (fromPlayer == collidedAtk->fromPlayer) {
					continue;
				}
				// Perform the attack triangle!!
				if (attackType == STAB && collidedAtk->attackType == SLASH) {
					collidedAtk->parent->onHit(damage, facingLeft);
					cout << fromPlayer << endl;
				} else if (attackType == SLASH && collidedAtk->attackType == SWIPE) {
					collidedAtk->parent->onHit(damage, facingLeft);
					cout << fromPlayer << endl;
				} else if (attackType == SWIPE && collidedAtk->attackType == STAB) {
					collidedAtk->parent->onHit(damage, facingLeft);
					cout << fromPlayer << endl;
				}
			}
			//if (facingLeft) cout << collidedEnt->tag << endl;
		}
	}
	this->timeToNextFrame -= dt;
	if (this->timeToNextFrame <= 0) {
		this->frameNum += 1;
		this->timeToNextFrame = maxTimeToNextFrame;
	}
	this->lifetime -= dt;
	if (this->lifetime <= 0) {
		this->dead = true;
	}
}