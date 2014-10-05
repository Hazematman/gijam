#ifndef ATTACK_SWIPE_HPP
#define ATTACK_SWIPE_HPP
#include "attack.hpp"

#define SWIPE_FRAME_LENGTH 0.1

class AttackSwipe : public Attack {
public:
	AttackSwipe();
	AttackSwipe(int Damage, float lifetime, bool facingLeft, bool fromPlayer);
};

#endif