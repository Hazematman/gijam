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
	this->body.width =  body.width==0 ? spriteSize.x : body.width;
	this->body.height = body.height==0 ? spriteSize.y : body.height;
}
