#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include "SFML/System.hpp"
#include "phys.hpp"

class Player {
public:
	RigidBody rb;
	sf::Sprite sprite;
	sf::Texture texture;
	bool isMovingLeft, isMovingRight;
	Player();
	void setSprite(std::string filename);
	void render(sf::RenderWindow &screen);
	void update(float dt);
};
#endif
