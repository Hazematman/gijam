#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include "SFML/System.hpp"
#include "phys.hpp"
#include "entity.hpp"

class Player : public Entity {
public:
	float speed;
	bool isMovingLeft, isMovingRight;
	Player();
	void render(sf::RenderWindow &screen);
	void update(float dt);
};
#endif
