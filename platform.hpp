#ifndef PLATFORM_HPP
#define PLATFORM_HPP
#include <iostream>
#include "SFML/System.hpp"
#include "phys.hpp"

class Platform {
public:
	RigidBody rb;
	sf::Sprite sprite;
	sf::Texture texture;
	Platform();
	//void setPos(float x, float y);
	void setSprite(std::string filename);
	void render(sf::RenderWindow &screen);
	void update(float dt);
};
#endif