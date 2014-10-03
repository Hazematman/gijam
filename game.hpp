#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "phys.hpp"
#include "player.hpp"

class Game {
	private:
		sf::RenderWindow screen;
		PhysWorld world;
		Player p;
	public:
		bool init();
		int run();
		void  update(float dt);
		void render();
};

#endif
