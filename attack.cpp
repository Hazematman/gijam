#include "attack.hpp"

Attack::Attack() {
	this->frameNum = 0;
}

void Attack::render(sf::RenderWindow &screen) {
	sprite.setPosition(pos);
	sprite.setTextureRect(sf::IntRect(32*this->frameNum,32,32,32));
	screen.draw(this->sprite);
}
