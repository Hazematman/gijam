#ifndef ATTACK_SLASH_HPP
#define ATTACK_SLASH_HPP
#include "attack.hpp"

#define SLASH_FRAME_LENGTH 0.1

class AttackSlash : public Attack {
public:
	AttackSlash();
	AttackSlash(int Damage, float lifetime, bool facingLeft, bool fromPlayer);
};

#endif