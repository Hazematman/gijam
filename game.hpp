#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "phys.hpp"
#include "player.hpp"
#include "platform.hpp"

class Game {
	private:
		sf::RenderWindow screen;
		PhysWorld world;
		Player p;
		Platform plat;
	public:
		bool init();
		int run();
		void update(float dt);
		void render();
};

#endif
