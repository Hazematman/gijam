#ifndef ATTACK_STAB_HPP
#define ATTACK_STAB_HPP
#include "attack.hpp"
#include <iostream>

class AttackStab : public Attack {
public:
	AttackStab();
	AttackStab(int Damage, float lifetime, bool facingLeft);
	bool facingLeft;
	int damage;
	float lifetime;
	void update(float dt);
};

#endif
