#ifndef PLANT_HPP
#define PLANT_HPP
#include "entity.hpp"

class Plant : public Entity{
	public:
		int currentAnim;
		float currentFrame;
		void init();
		void render(sf::RenderWindow &screen);
		void update(float dt);
};

#endif
