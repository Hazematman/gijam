#include "attack.hpp"

Attack::Attack(){
}

void Attack::render(sf::RenderWindow &screen){
	sprite.setPosition(pos);
	sprite.setTextureRect(sf::IntRect(0,0,32,32));
	screen.draw(this->sprite);
}
