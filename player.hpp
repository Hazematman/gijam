#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "SFML/System.hpp"
#include "phys.hpp"

class Player {
public:
	RigidBody rb;
	sf::Sprite sprite;
	sf::Texture texture;
	Player();
	Player(sf::Texture, float x, float y);
	void render(sf::RenderWindow &screen);
	void update(float dt);
};
#endif
