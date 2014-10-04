#ifndef ATTACK_STAB_HPP
#define ATTACK_STAB_HPP
#include "attack.hpp"
#include <iostream>

#define STAB_FRAME_LENGTH 0.1

class AttackStab : public Attack {
public:
	AttackStab();
	AttackStab(int Damage, float lifetime, bool facingLeft);
	bool facingLeft;
	int damage;
	float lifetime;
	float timeToNextFrame;
	void update(float dt);
};

#endif
