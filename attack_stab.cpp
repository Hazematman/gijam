#include "attack_stab.hpp"

AttackStab::AttackStab() {
	this->damage = 0;
}

AttackStab::AttackStab(int damage) {
	this->damage = damage;
}

void AttackStab::update(float dt) {
	for (RigidBody* collidedRB : this->collided) {
		Entity* collidedEnt = (Entity*) collidedRB;
		if (collidedEnt->onHit(damage)) {
			this->dead = true;
		};
	}
}