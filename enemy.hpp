#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <iostream>
#include "SFML/System.hpp"
#include "phys.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "attack.hpp"
#include "attack_stab.hpp"
#include <cmath>
#include <memory>

class Enemy : public Entity {
public:
	sf::Texture sTex;
	sf::Sprite sSpr;
	float speed;
	bool isMovingLeft, isMovingRight;
	bool facingLeft;
	float jumpPowerLeft;
	float attackCd;
	float currentFrame;
	int currentAnim;
	std::vector<std::unique_ptr<Attack>> aliveAttacks;
	Enemy();
	void render(sf::RenderWindow &screen);
	void update(float dt);
	bool onHit(int damage);
};
#endif
