#include "game.hpp"
#include "phys.hpp"
#include "SFML/System.hpp"

class Player {
public:
	RigidBody rb;
	sf::Sprite sprite;
	Player(sf::Sprite, float x, float y);
	void render();
	void update(float dt);
};