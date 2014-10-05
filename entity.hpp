#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Audio.hpp>
#include "phys.hpp"

extern sf::SoundBuffer stabBuf;
extern sf::Sound stabSnd;

#define INVULN_WINDOW 0.5

class Entity : public RigidBody {
	public:
		sf::Sprite sprite;
		sf::Texture texture;
		Entity();
		void setSprite(std::string filename);
		virtual void render(sf::RenderWindow &screen){};
		virtual void update(float dt){};
		virtual bool onHit(int damage, bool facingLeft){return false;};	// callback for being hit with damage, returns whether an attack "connected"
};

#endif
