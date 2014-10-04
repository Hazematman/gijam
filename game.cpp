#include "game.hpp"
#include <iostream>
using namespace std;

bool Game::init(){
	screen.create(sf::VideoMode(800,600), "Game");
	p.setSprite("./data/images/Marisa_Stand_01.png");	
	world.bodies.push_back(&p.rb);
	world.gravity = sf::Vector2f(0,9.81);
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
			} else if (e.type == sf::Event::KeyPressed){
				if (e.key.code == sf::Keyboard::Left) {
					p.rb.vel = sf::Vector2f(-1.,0.);
				} else if (e.key.code == sf::Keyboard::Right) { 
					p.rb.vel = sf::Vector2f(+1.,0.);
				};
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
}

void Game::render(){
	p.render(screen);
}
