#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include "SFML/System.hpp"
#include "phys.hpp"
#include "entity.hpp"
#include <cmath>

#define MAX_JUMP 1

class Player : public Entity {
public:
	bool isMovingLeft, isMovingRight;
	float jumpPowerLeft;
	Player();
	void render(sf::RenderWindow &screen);
	void update(float dt);
};
#endif
