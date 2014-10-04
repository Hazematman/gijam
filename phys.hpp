#ifndef PHYS_HPP
#define PHYS_HPP
#include <vector>
#include <SFML/Graphics.hpp>

class RigidBody {
	public:
		std::string tag;
		std::vector<RigidBody*> collided;
		sf::Rect<float> body;
		sf::Vector2f vel;
		sf::Vector2f pos;
		bool moves;
		RigidBody(float x, float y, float dx, float dy);
		RigidBody();
};

class PhysWorld {
	public:
		std::vector<RigidBody*> bodies;
		sf::Vector2f gravity;
		void update(float dt);
};

#endif
