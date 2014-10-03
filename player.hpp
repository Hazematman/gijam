#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "SFML/System.hpp"
#include "phys.hpp"

class Player {
public:
	RigidBody rb;
	sf::Sprite sprite;
	Player();
	Player(sf::Sprite, float x, float y);
	void render();
	void update(float dt);
};
#endif
