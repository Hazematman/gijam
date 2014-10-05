#include "attack_slash.hpp"
using namespace std;

AttackSlash::AttackSlash() {
	this->attackType = SLASH;
	this->timeToNextFrame = SLASH_FRAME_LENGTH;
	this->maxTimeToNextFrame = SLASH_FRAME_LENGTH;
	this->framePos = 2;
}

AttackSlash::AttackSlash(int damage, float lifetime, bool facingLeft, bool fromPlayer) {
	this->damage = damage;
	this->lifetime = lifetime;
	this->sprite.setScale((facingLeft ? -2 : 2),2);
	this->body = sf::Rect<float> (0,200,32,32);
	this->facingLeft = facingLeft;
	this->timeToNextFrame = SLASH_FRAME_LENGTH;
	this->maxTimeToNextFrame = SLASH_FRAME_LENGTH;
	this->fromPlayer = fromPlayer;
	this->attackType = SLASH;
	this->framePos = (fromPlayer ? 2 : 6);
}