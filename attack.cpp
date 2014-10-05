#include "attack.hpp"

Attack::Attack() {
	this->frameNum = 0;
	this->framePos = 1;
}

void Attack::render(sf::RenderWindow &screen) {
	sf::RectangleShape rect(sf::Vector2f(body.width,body.height));
	rect.setPosition(body.left,body.top);
	//screen.draw(rect);
	sprite.setPosition(pos);
	sprite.setTextureRect(sf::IntRect(32*this->frameNum,framePos*32,32,32));
	screen.draw(this->sprite);
}
