#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include "SFML/System.hpp"
#include "phys.hpp"
#include "entity.hpp"
#include "attack.hpp"
#include "attack_stab.hpp"
#include <cmath>
#include <memory>

#define MAX_JUMP 1
#define STAB_CD 0.7

class Player : public Entity {
public:
	float speed;
	bool isMovingLeft, isMovingRight;
	bool facingLeft;
	float jumpPowerLeft;
	float attackCd;
	std::vector<std::unique_ptr<Attack>> aliveAttacks;
	Player();
	void render(sf::RenderWindow &screen);
	void update(float dt);
};
#endif
