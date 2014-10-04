#include "attack_stab.hpp"

void AttackStab::update(float dt) {
	for (RigidBody* collidedRB : this->collided) {
		Entity* collidedEnt = (Entity*) collidedRB;

	}
}