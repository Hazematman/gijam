#include <sstream>
#include "game.hpp"
#include "plant.hpp"
using namespace std;

PhysWorld *gworld;
Player *gplayer;
Floor f;

sf::Texture menuTex;
sf::Texture bgTex;
sf::Sprite bgSpr;
sf::Sprite menuSpr;
sf::SoundBuffer stabBuf;
sf::SoundBuffer slashBuf;
sf::SoundBuffer atkBuf;
sf::Sound stabSnd;
sf::Sound slashSnd;
sf::Sound atkSnd;

sf::Font mainFont;

Plant p1;
Plant p2;
Plant p3;

enum State {
	MENU,
	GAME,
};

State state = MENU;

string intToStr(int num){
	stringstream ss;
	ss << num;
	return ss.str();
}

bool Game::init(){
	screen.create(sf::VideoMode(800,600), "Stab Beats Slash Beats Swipe");
	if (stabBuf.loadFromFile("./data/sounds/sword_sound.wav")
		&& slashBuf.loadFromFile("./data/sounds/melee_sound.wav")
		&& atkBuf.loadFromFile("./data/sounds/animal_melee_sound.wav")
		&& enemyDeathFXBuf.loadFromFile("./data/sounds/enemy_death_sfx.wav")
		&& playerDeathFXBuf.loadFromFile("./data/sounds/player_death_sfx.wav")) {
		cout << "Sound loaded successfully" << endl;
	}
	stabSnd.setBuffer(stabBuf);
	slashSnd.setBuffer(slashBuf);
	atkSnd.setBuffer(atkBuf);
	enemyDeathFX.setBuffer(enemyDeathFXBuf);
	playerDeathFX.setBuffer(playerDeathFXBuf);
	mainFont.loadFromFile("./data/fonts/PressStart2P.ttf");
	scoreText.setFont(mainFont);
	score = 0;
	redrawScore();
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
	shakeIntensity = 0;
	srand (time(NULL));

	menuTex.loadFromFile("./data/images/title.png");
	menuSpr.setTexture(menuTex);
	bgTex.loadFromFile("./data/images/background.png");
	bgSpr.setTexture(bgTex);
	p1.init();
	p1.pos = sf::Vector2f(0,600-64);
	p2.init();
	p2.pos = sf::Vector2f(800-64,600-64);
	p3.init();
	p3.pos = sf::Vector2f(800-128, 600-64);
	addPlatform(310,290);
	addPlatform(470,310);
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
			if(e.type == sf::Event::KeyPressed && state == MENU){
				redrawScore();
				state = GAME;
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

void Game::redrawScore() {
	scoreText.setString("Score: " + intToStr(score));
	scoreText.setPosition(400-(int) (scoreText.getGlobalBounds().width/2),50);
}

void Game::update(float dt){
	if(state != MENU){
		// The worst hack you ever did see
		world.removeBody(gplayer);
		world.bodies.push_back(gplayer);
		
		world.update(dt);
		gplayer->update(dt);
		p1.update(dt);
		p2.update(dt);
		p3.update(dt);
		for (int i = 0; i < enemies.size(); i++) {
			Enemy* enemy = enemies.at(i).get();
			if (enemy->dead) {
				shakeIntensity = MAX_SHAKE_INTENSITY/2;
				enemyDeathFX.play();
				score++;
				redrawScore();
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
			int directionToSpawn = rand();
			if (directionToSpawn%5 < 2) {
				addEnemy(800, 0);
			} else if (directionToSpawn%5 < 4){
				addEnemy(-64, 0);
			} else {
				addEnemy(400, -64);
			}
		}
		if (gplayer->dead) {
			state = MENU;
			playerDeathFX.play();
			shakeIntensity = MAX_SHAKE_INTENSITY;
			gplayer->Init();
			world.bodies.push_back(gplayer);
			for (int i = 0; i < enemies.size(); ) {	// Empty the enemies
				Enemy* enemy = enemies.at(i).get();
				enemy->dead = true;
				for (int i = 0; i < enemy->aliveAttacks.size(); i++) {
					Attack* thisAttack = enemy->aliveAttacks.at(i).get();
					thisAttack->dead = true;
					gworld->removeBody(thisAttack);
				}
				gworld->removeBody(enemy);
				enemies.erase(enemies.begin());
			}
			enemiesToSpawn = 1;
			timeUntilNextSpawn = 0;
			score = 0;
		}
	}
	if (shakeIntensity > 0) {
		sf::View view = screen.getView();
		view.setCenter(fmod(rand(), shakeIntensity) - shakeIntensity/2+view.getSize().x/2, fmod(rand(), shakeIntensity) - shakeIntensity/2+view.getSize().y/2);
		shakeIntensity -= MAX_SHAKE_INTENSITY*dt*2;
		screen.setView(view);
	} else {
		// Should be unecessary to do this
		sf::View view = screen.getView();
		view.setCenter(+view.getSize().x/2, +view.getSize().y/2);
		screen.setView(view);
	}
}

void Game::render(){
	screen.draw(bgSpr);
	gplayer->render(screen);
	p1.render(screen);
	p2.render(screen);
	p3.render(screen);
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
	if(state == MENU){
		screen.draw(menuSpr);
	}
	screen.draw(scoreText);
}

void Game::addPlatform(int x, int y) {
	this->plats.push_back(unique_ptr<Platform>(new Platform()));
	Platform *plat = ((Platform*) this->plats.back().get());
	plat->setSprite("./data/images/platforms.png");
	plat->pos = sf::Vector2f(x,y);
	plat->body.left = x;
	plat->body.top = y;
	world.bodies.push_back(plat);
}

void Game::addEnemy(int x, int y) {
	this->enemies.push_back(unique_ptr<Enemy>(new Enemy()));
	Enemy *enemy = ((Enemy*) this->enemies.back().get());
	enemy->setSprite("./data/images/charsheet.png");
	enemy->pos = sf::Vector2f(x,y);
	world.bodies.push_back(enemy);
}
