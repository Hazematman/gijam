#include "game.hpp"
using namespace std;

PhysWorld *gworld;
Player *gplayer;
Floor f;

bool Game::init(){
	screen.create(sf::VideoMode(800,600), "Game");
	f.init(600,300);
	f.pos = sf::Vector2f(100,400);
	world.bodies.push_back(&f);
	p.setSprite("./data/images/charsheet.png");
	world.bodies.push_back(&p);
	world.gravity = sf::Vector2f(0,GRAVITY);
	gworld = &world;
	gplayer = &p;
	enemiesToSpawn = 1;
	timeUntilNextSpawn = 0;
	srand (time(NULL));
	return true;
}

int Game::run(){
	if(init() == false)
		return EXIT_FAILURE;
	sf::Event e;
	sf::Clock dtTimer;
	dtTimer.restart();
	float dt = 0;
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
	for (int i = 0; i < enemies.size(); i++) {
		Enemy* enemy = enemies.at(i).get();
		if (enemy->dead) {
			// Add two enemies for every dead enemy
			enemiesToSpawn += 2;
			enemies.erase(enemies.begin() + i);
			i--;
			gworld->removeBody(enemy);
			continue;
		}
		enemy->update(dt);
	}
	timeUntilNextSpawn -= dt;
	if (timeUntilNextSpawn < 0 && enemiesToSpawn > 0) {
		enemiesToSpawn--;
		timeUntilNextSpawn = ENEMY_SPAWN_CD;
		if (rand() < 50) {
			addEnemy(800, 0);
		} else {
			addEnemy(-100, 0);
		}
	}
}

void Game::render(){
	gplayer->render(screen);
	f.render(screen);
	for (int i = 0; i < this->plats.size(); i++) {
		Platform* plat = plats.at(i).get();
		plat->render(screen);
	}
	for (int i = 0; i < this->enemies.size(); i++) {
		Enemy* enemy = enemies.at(i).get();
		enemy->render(screen);
	}
	for(RigidBody *r : world.bodies){
		//r->render(screen);
	}
}

void Game::addPlatform(int x, int y) {
	this->plats.push_back(unique_ptr<Platform>(new Platform()));
	Platform *plat = ((Platform*) this->plats.back().get());
	plat->setSprite("./data/images/platforms.png");
	world.bodies.push_back(plat);
	plat->pos = sf::Vector2f(x,y);
}

void Game::addEnemy(int x, int y) {
	this->enemies.push_back(unique_ptr<Enemy>(new Enemy()));
	Enemy *enemy = ((Enemy*) this->enemies.back().get());
	enemy->setSprite("./data/images/charsheet.png");
	world.bodies.push_back(enemy);
	enemy->pos = sf::Vector2f(x,y);
}
