#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "phys.hpp"
#include "player.hpp"
#include "platform.hpp"
#include "enemy.hpp"
#include <memory>

class Game {
	private:
		sf::RenderWindow screen;
		PhysWorld world;
		Player p;
		Enemy e;
		std::vector<std::unique_ptr<Platform>> plats;
	public:
		bool init();
		int run();
		void update(float dt);
		void render();
		void addPlatform(int x, int y);
};

#endif
