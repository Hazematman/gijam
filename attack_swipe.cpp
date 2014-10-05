#include "attack_swipe.hpp"
using namespace std;

AttackSwipe::AttackSwipe() {
	this->attackType = SWIPE;
	this->timeToNextFrame = SWIPE_FRAME_LENGTH;
	this->maxTimeToNextFrame = SWIPE_FRAME_LENGTH;
	this->framePos = 3;
}

AttackSwipe::AttackSwipe(int damage, float lifetime, bool facingLeft, bool fromPlayer) {
	this->damage = damage;
	this->lifetime = lifetime;
	this->sprite.setScale((facingLeft ? -2 : 2),2);
	this->body = sf::Rect<float> (0,200,32,32);
	this->facingLeft = facingLeft;
	this->timeToNextFrame = SWIPE_FRAME_LENGTH;
	this->maxTimeToNextFrame = SWIPE_FRAME_LENGTH;
	this->fromPlayer = fromPlayer;
	this->attackType = SWIPE;
	this->framePos = (fromPlayer ? 3 : 7);
}