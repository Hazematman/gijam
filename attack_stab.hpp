#ifndef ATTACK_STAB_HPP
#define ATTACK_STAB_HPP
#include "Attack.hpp"

class AttackStab : public Attack {
public:
	AttackStab();
	AttackStab(Damage);
	int damage;
	void update(float dt);
};

#endif