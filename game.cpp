#include "game.hpp"
using namespace std;

bool Game::init(){
	screen.create(sf::VideoMode(800,600), "Game");
	return true;
}

int Game::run(){
	if(init() == false)
		return EXIT_FAILURE;
	sf::Event e;
	sf::Clock dtTimer;
	float dt;
	while(screen.isOpen()){
		while(screen.pollEvent(e)){
			if(e.type == sf::Event::Closed){
				screen.close();
			}
		}

		screen.clear(sf::Color::Black);
		update(dt);
		screen.display();
		render();
		dt = dtTimer.restart().asSeconds();
	}
	return EXIT_SUCCESS;
}

void Game::update(float dt){
}

void Game::render(){
}
