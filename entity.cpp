#include "entity.hpp"
using namespace std;

Entity::Entity(){
	this->rb = RigidBody(0,0,0,0);
}

void Entity::setSprite(string filename){
	this->texture.loadFromFile(filename);
	this->sprite.setTexture(texture);
	sf::Vector2u spriteSize = sprite.getTexture()->getSize();
	this->rb.body.left = rb.pos.x;
	this->rb.body.top = rb.pos.y;
	this->rb.body.width = spriteSize.x;
	this->rb.body.height = spriteSize.y;
}
