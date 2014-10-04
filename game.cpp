#include "game.hpp"
#include <iostream>
using namespace std;

bool Game::init(){
	screen.create(sf::VideoMode(800,600), "Game");
	plat.setSprite("./data/images/DownArrow.png");
	p.setSprite("./data/images/Marisa_Stand_01.png");
	world.bodies.push_back(&p);
	world.bodies.push_back(&plat);
	world.gravity = sf::Vector2f(0,GRAVITY);
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
		render();
		screen.display();
		dt = dtTimer.restart().asSeconds();
	}
	return EXIT_SUCCESS;
}

void Game::update(float dt){
	world.update(dt);
	p.update(dt);
}

void Game::render(){
	p.render(screen);
	plat.render(screen);
}
