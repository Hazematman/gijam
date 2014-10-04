#ifndef ATTACK_STAB_HPP
#define ATTACK_STAB_HPP
#include "attack.hpp"
#include <iostream>

class AttackStab : public Attack {
public:
	AttackStab();
	AttackStab(int Damage, int lifetime, bool facingLeft);
	bool facingLeft;
	int damage;
	int lifetime;
	void update(float dt);
};

#endif
