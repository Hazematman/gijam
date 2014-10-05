#include "attack_stab.hpp"
using namespace std;

AttackStab::AttackStab() {
	this->attackType = STAB;
	this->timeToNextFrame = STAB_FRAME_LENGTH;
	this->maxTimeToNextFrame = STAB_FRAME_LENGTH;
	this->framePos = 1;
}

AttackStab::AttackStab(int damage, float lifetime, bool facingLeft, bool fromPlayer) {
	this->damage = damage;
	this->lifetime = lifetime;
	this->sprite.setScale((facingLeft ? -2 : 2),2);
	this->body = sf::Rect<float> (0,200,32,32);
	this->facingLeft = facingLeft;
	this->timeToNextFrame = STAB_FRAME_LENGTH;
	this->maxTimeToNextFrame = STAB_FRAME_LENGTH;
	this->fromPlayer = fromPlayer;
	this->attackType = STAB;
	this->framePos = (fromPlayer ? 1 : 5);
}