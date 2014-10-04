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
#define STAB_CD 0.8
#define MAX_WALK_SPEED 60

enum Anims {
	IDLE,
	WALK,
	KWALK,
};

class Player : public Entity {
public:
	float speed;
	bool isMovingLeft, isMovingRight;
	bool facingLeft;
	float currentFrame;
	int currentAnim;
	float jumpPowerLeft;
	float attackCd;
	int HP;
	std::vector<std::unique_ptr<Attack>> aliveAttacks;
	Player();
	void render(sf::RenderWindow &screen);
	void update(float dt);
	bool onHit(int damage);
};

extern Player *gplayer;
#endif
