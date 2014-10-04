#ifndef ATTACK_STAB_HPP
#define ATTACK_STAB_HPP
#include "attack.hpp"

class AttackStab : public Attack {
public:
	AttackStab();
	AttackStab(int Damage);
	int damage;
	void update(float dt);
};

#endif