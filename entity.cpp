#include "entity.hpp"
using namespace std;

Entity::Entity(){
	//this->rb = RigidBody(0,0,0,0);
	this->dead = false;
}

void Entity::setSprite(string filename){
	this->texture.loadFromFile(filename);
	this->sprite.setTexture(texture);
	sf::Vector2u spriteSize = sprite.getTexture()->getSize();
	this->body.left = pos.x;
	this->body.top = pos.y;
	this->body.width = spriteSize.x;
	this->body.height = spriteSize.y;
}
