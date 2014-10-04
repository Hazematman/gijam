#include "attack_stab.hpp"
using namespace std;

AttackStab::AttackStab() {
	this->damage = 0;
	this->lifetime = 10;
	this->tag = "attack";
	this->sprite.setScale(2,2);
	this->facingLeft = false;
	this->moves = false;
	this->timeToNextFrame = STAB_FRAME_LENGTH;
}

AttackStab::AttackStab(int damage, float lifetime, bool facingLeft) {
	this->damage = damage;
	this->lifetime = lifetime;
	this->tag = "attack";
	this->sprite.setScale((facingLeft ? -2 : 2),2);
	this->facingLeft = facingLeft;
	this->moves = false;
	this->timeToNextFrame = STAB_FRAME_LENGTH;
}

void AttackStab::update(float dt) {
	if (!this->dead) {
		for (RigidBody* collidedRB : this->collided) {
			Entity* collidedEnt = (Entity*) collidedRB;
			collidedEnt->tag != "player" && collidedEnt->onHit(damage);
		}
	}
	this->timeToNextFrame -= dt;
	if (this->timeToNextFrame <= 0) {
		this->frameNum += 1;
		this->timeToNextFrame = STAB_FRAME_LENGTH;
	}
	this->lifetime -= dt;
	if (this->lifetime <= 0) {
		this->dead = true;
		cout << "ded" << endl;
	}
}
