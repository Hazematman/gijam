#ifndef ATTACK_HPP
#define ATTACK_HPP
#include "entity.hpp"
#include <iostream>

class Attack : public Entity {
public:
	Attack();
	int frameNum;
	void render(sf::RenderWindow &screen);
	virtual void update(float dt){std::cout << "virt" << std::endl;};
};

#endif