#include "attack_stab.hpp"
using namespace std;

AttackStab::AttackStab() {
	this->damage = 0;
	this->lifetime = 10;
	this->tag = "attack";
	this->sprite.setScale(2,2);
	this->facingLeft = false;
}

AttackStab::AttackStab(int damage, int lifetime, bool facingLeft) {
	this->damage = damage;
	this->lifetime = lifetime;
	this->tag = "attack";
	this->sprite.setScale((facingLeft ? -2 : 2),2);
	this->facingLeft = facingLeft;
}

void AttackStab::update(float dt) {
	cout << "update" << endl;
	if (!this->dead) {
		for (RigidBody* collidedRB : this->collided) {
			Entity* collidedEnt = (Entity*) collidedRB;
			if (collidedEnt->tag != "player" && collidedEnt->onHit(damage)) {
				this->dead = true;
			};
		}
	}
	this->lifetime -= dt;
	if (this->lifetime <= 0) {
		this->dead = true;
		cout << "ded" << endl;
	}
}
