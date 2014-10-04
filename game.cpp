#include "game.hpp"
using namespace std;

PhysWorld *gworld;
Player *gplayer;

bool Game::init(){
	screen.create(sf::VideoMode(800,600), "Game");
	this->addPlatform(10,300);
	this->addPlatform(100,300);
	p.setSprite("./data/images/charsheet.png");
	e.setSprite("./data/images/charsheet.png");
	world.bodies.push_back(&p);
	world.bodies.push_back(&e);
	world.gravity = sf::Vector2f(0,GRAVITY);
	gworld = &world;
	gplayer = &p;
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
	gplayer->update(dt);
	e.update(dt);
}

void Game::render(){
	gplayer->render(screen);
	for (int i = 0; i < this->plats.size(); i++) {
		Platform* plat = plats.at(i).get();
		plat->render(screen);
	}
	e.render(screen);
}

void Game::addPlatform(int x, int y) {
	this->plats.push_back(unique_ptr<Platform>(new Platform()));
	Platform *plat = ((Platform*) this->plats.back().get());
	plat->setSprite("./data/images/DownArrow.png");
	world.bodies.push_back(plat);
	plat->pos = sf::Vector2f(x,y);
}