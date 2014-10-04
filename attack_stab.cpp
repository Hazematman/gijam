#include "attack_stab.hpp"

AttackStab::AttackStab(){
}

AttackStab::AttackStab(int Damage){
}

void AttackStab::update(float dt) {
	for (RigidBody* collidedRB : this->collided) {
		Entity* collidedEnt = (Entity*) collidedRB;
		//if 
	}
}
