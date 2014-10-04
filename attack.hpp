#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "entity.hpp"

class Attack : public Entity {
public:
	Attack();
	void render(sf::RenderWindow &screen);
	virtual void update(float dt){ };
};

#endif