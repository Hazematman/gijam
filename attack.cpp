#include "attack.hpp"

Attack::Attack(){
}

void Attack::render(sf::RenderWindow &screen){
	sprite.setPosition(pos);
	screen.draw(this->sprite);
}
