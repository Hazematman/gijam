#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "phys.hpp"

#define INVULN_WINDOW 1

class Entity : public RigidBody {
	public:
		sf::Sprite sprite;
		sf::Texture texture;
		float invulnWindow;
		Entity();
		void setSprite(std::string filename);
		virtual void render(sf::RenderWindow &screen){};
		virtual void update(float dt){};
		virtual bool onHit(int damage, bool facingLeft){return false;};	// callback for being hit with damage, returns whether an attack "connected"
};

#endif
