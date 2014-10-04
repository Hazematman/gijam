#include "platform.hpp"
using namespace std;

Platform::Platform(){
	//this->rb = RigidBody(10, 300, 100, 10);
	this->pos = sf::Vector2f(10,300);
	this->moves = false;
	this->tag = "platform";
	this->body = sf::FloatRect(0,0,15*4,4*4);
	this->sprite.setTextureRect(sf::IntRect(0,0,15,4));
	this->sprite.setScale(4,4);
}

void Platform::update(float dt){
}

void Platform::render(sf::RenderWindow &screen){
	sprite.setPosition(pos);
	screen.draw(this->sprite);
}

void Floor::init(int xsize, int ysize){
	this->moves = false;
	this->tag = "platform";
	rect.setSize(sf::Vector2f(xsize, ysize));
	body = sf::FloatRect(0,0, xsize, ysize);
}

void Floor::update(float dt){
}

void Floor::render(sf::RenderWindow &screen){
	rect.setPosition(pos);
	screen.draw(rect);
}
