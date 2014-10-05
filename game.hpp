#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "phys.hpp"
#include "player.hpp"
#include "platform.hpp"
#include "enemy.hpp"
#include <memory>
#include <cstdlib>
#include <time.h>

#define ENEMY_SPAWN_CD 2
#define MAX_SHAKE_INTENSITY 10

class Game {
	private:
		sf::RenderWindow screen;
		PhysWorld world;
		Player p;
		std::vector<std::unique_ptr<Platform>> plats;
		std::vector<std::unique_ptr<Enemy>> enemies;
		float timeUntilNextSpawn;
		int enemiesToSpawn;
		sf::Text scoreText;
		int score;
		float shakeIntensity;
		sf::SoundBuffer enemyDeathFXBuf;
		sf::SoundBuffer playerDeathFXBuf;
		sf::Sound enemyDeathFX;
		sf::Sound playerDeathFX;
	public:
		bool init();
		int run();
		void update(float dt);
		void render();
		void addPlatform(int x, int y);
		void addEnemy(int x, int y);
		void redrawScore();
};

#endif
