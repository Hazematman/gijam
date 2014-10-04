#include "attack.hpp"

void Attack::render(sf::RenderWindow &screen){
	sprite.setPosition(pos);
	screen.draw(this->sprite);
}