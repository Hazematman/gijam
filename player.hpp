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
#include <cstdlib>

#define MAX_JUMP 0.8
#define STAB_CD 0.8
#define MAX_WALK_SPEED 60

class Player : public Entity {
public:
	sf::Texture sTex;
	sf::Sprite sSpr;
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
	void Init();
	void render(sf::RenderWindow &screen);
	void update(float dt);
	bool onHit(int damage, bool facingLeft);
};

extern Player *gplayer;
#endif
