#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>

class Game {
	private:
		sf::RenderWindow screen;
	public:
		bool init();
		int run();
		void  update(float dt);
		void render();
};

#endif
