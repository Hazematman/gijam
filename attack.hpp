#ifndef ATTACK_HPP
#define ATTACK_HPP
#include "entity.hpp"
#include <iostream>

enum AttackTypes {
	STAB,
	SLASH,
	SWIPE
};

class Attack : public Entity {
public:
	Attack();
	int frameNum;
	int framePos;
	int attackType;
	Entity* parent;
	bool facingLeft;
	bool fromPlayer;
	int damage;
	float lifetime;
	float timeToNextFrame;
	float maxTimeToNextFrame;
	void render(sf::RenderWindow &screen);
	void update(float dt);
};

#endif
