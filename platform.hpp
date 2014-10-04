#ifndef PLATFORM_HPP
#define PLATFORM_HPP
#include <iostream>
#include "SFML/System.hpp"
#include "phys.hpp"
#include "entity.hpp"

class Platform : public Entity {
public:
	Platform();
	void render(sf::RenderWindow &screen);
	void update(float dt);
};
#endif
