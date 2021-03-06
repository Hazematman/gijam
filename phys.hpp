#ifndef PHYS_HPP
#define PHYS_HPP
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#define GRAVITY 1000
#define DRAG 0.9

class RigidBody {
	public:
		std::string tag;
		std::vector<RigidBody*> collided;
		sf::Rect<float> body;
		sf::Vector2f vel;
		sf::Vector2f pos;
		float invulnWindow;
		bool dead;	// Remove from world
		bool moves;
		RigidBody(float x, float y, float dx, float dy);
		RigidBody();
		void render(sf::RenderWindow &screen);
};

class PhysWorld {
	public:
		std::vector<RigidBody*> bodies;
		sf::Vector2f gravity;
		void update(float dt);
		void removeBody(RigidBody* body);

};

extern PhysWorld *gworld;
#endif
