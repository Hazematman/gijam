#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "phys.hpp"

class Entity {
	public:
		RigidBody rb;
		sf::Sprite sprite;
		sf::Texture texture;
		Entity();
		void setSprite(std::string filename);
		virtual void render(sf::RenderWindow &screen){};
		virtual void update(float dt){};
};

#endif
