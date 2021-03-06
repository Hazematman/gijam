#include "iostream"
#include "player.hpp"
using namespace std;

#define FRAMERATE 6
#define WFRAMERATE 8
#define KFRAMERATE 10

#define UPSPEED 30

enum Anims {
	IDLE,
	WALK,
	KWALK,
	JUMP,
	HURT
};

Player::Player(){
	Init();
}

void Player::Init(){
	this->dead = false;
	this->speed = 30;
	this->pos = sf::Vector2f(400,200);
	this->tag = "player";
	this->body = sf::Rect<float> (0,200,32,64);
	this->isMovingLeft = false;
	this->isMovingRight = false;
	this->facingLeft = false;
	this->sprite.setScale(2,2);
	this->attackCd = 0;
	this->HP = 40;
	this->vel.x = 0;
	this->vel.y = 30;

	this->currentFrame = 0;
	this->currentAnim = 0;

	this->sTex.loadFromFile("./data/images/attacksheet.png");
	this->sSpr.setTexture(this->sTex);
	this->sSpr.setScale(2,2);
	this->sSpr.setTextureRect(sf::IntRect(0,0,32,32));
}

void Player::update(float dt){
	// Horizontal Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		isMovingLeft = true;
		vel += sf::Vector2f(-speed,0.);
		currentAnim = WALK;
	} else if (isMovingLeft) {
		isMovingLeft = false;
		if(vel.x != 0) {
			vel -= sf::Vector2f(-speed,0.);
		}
		currentAnim = IDLE;
		currentFrame = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		isMovingRight = true;
		currentAnim = WALK;
		vel += sf::Vector2f(+speed,0.);
	} else if (isMovingRight) {
		isMovingRight = false;
		if(vel.x != 0) {
			vel -= sf::Vector2f(+speed,0.);
		}
		currentAnim = IDLE;
		currentFrame = 0;
	}
	if (this->attackCd <= 0 && isMovingLeft) {
		facingLeft = true;
		sprite.setScale(-2,2);
		sSpr.setScale(-2,2);
	} else if (this->attackCd <= 0 && isMovingRight) {
		facingLeft = false;
		sprite.setScale(+2,2);
		sSpr.setScale(+2,2);
	} 

	// Vertical Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->jumpPowerLeft > 0) {
		vel += sf::Vector2f(0.,-GRAVITY*this->jumpPowerLeft/MAX_JUMP*dt*13);
		this->jumpPowerLeft -= dt*10;
	} else {
		this->jumpPowerLeft = 0;
	}
	for (int i = 0; i < collided.size(); i++) {
		Entity* collidedEnt = (Entity*) collided.at(i);
		if (collidedEnt->tag == "platform" && vel.y == 0) {
			this->jumpPowerLeft = MAX_JUMP;
			continue;
		}
		// Jump onto people, pushing them away
		if (collidedEnt->moves && collidedEnt->pos.y > pos.y+body.height && collidedEnt->invulnWindow <= 0) {
			collidedEnt->invulnWindow = INVULN_WINDOW;
			collidedEnt->vel.x = (pos.x < collidedEnt->pos.x ? 250 : -250);
			cout << "PlayerJump" << collidedEnt->vel.x << endl;
		}
		if (invulnWindow-dt <= 0) {
			invulnWindow += dt;
		}
	}
	invulnWindow -= dt;

	// Attacks
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::C)) && this->attackCd <= 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			aliveAttacks.push_back(unique_ptr<Attack>(new AttackStab(10, STAB_CD, facingLeft, true)));
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			aliveAttacks.push_back(unique_ptr<Attack>(new AttackSlash(10, SLASH_CD, facingLeft, true)));
		} else {
			aliveAttacks.push_back(unique_ptr<Attack>(new AttackSwipe(10, SWIPE_CD, facingLeft, true)));
		}
		
		Attack *newatk = (this->aliveAttacks.back().get());
		//newatk->pos = this->pos + (this->facingLeft ? sf::Vector2f(35,-4) : sf::Vector2f(-4,-4));
		newatk->tag = "attack";
		newatk->parent = this;
		newatk->body = sf::Rect<float> (0,200,32,32);
		newatk->setSprite("./data/images/attacksheet.png");
		gworld->bodies.push_back(newatk);
		this->attackCd = STAB_CD;
		int soundToPlay = rand() % 3;
		if (soundToPlay == 0) {
			stabSnd.play();
		} else if (soundToPlay == 1) {
			slashSnd.play();
		} else {
			atkSnd.play();
		}
	}
	this->attackCd -= dt;

	for (int i = 0; i < this->aliveAttacks.size(); i++) {
		Attack *thisAttack = aliveAttacks.at(i).get();
		if (thisAttack->dead) {
			gworld->removeBody(thisAttack);
			this->aliveAttacks.erase(this->aliveAttacks.begin() + i);
			i--;
			continue;
		}

		thisAttack->update(dt);
	}


	if (invulnWindow > 0 && currentAnim != HURT) {
		currentAnim = HURT;
	}
	
	if(this->currentAnim == IDLE){
		currentFrame += FRAMERATE*dt;	
		currentFrame = fmod(currentFrame, 2);
	} else if(this->currentAnim == WALK){
		currentFrame += WFRAMERATE*dt;
		if(currentFrame > 3){
			currentAnim = KWALK;
			this->vel += sf::Vector2f(isMovingLeft? -UPSPEED : UPSPEED ,0);
		}
		currentFrame = fmod(currentFrame, 3);
	} else if(this->currentAnim == KWALK){
		currentFrame += KFRAMERATE*dt;
		currentFrame = fmod(currentFrame, 3);
	} else if (currentAnim == HURT) {
		currentFrame = 0;
	}

	if (pos.y > 600) {
		dead = true;
	}
}

void Player::render(sf::RenderWindow &screen){
	sprite.setTextureRect(sf::IntRect((int)this->currentFrame*16,(int)this->currentAnim*32,16,32));
	sprite.setPosition(pos);
	if(facingLeft){
		sprite.move(32,0);
	}
	sf::RectangleShape rect(sf::Vector2f(body.width,body.height));
	rect.setPosition(body.left,body.top);
	//screen.draw(rect);
	screen.draw(this->sprite);
	if(this->aliveAttacks.size() > 0){
		for (int i = 0; i < this->aliveAttacks.size(); i++) {
			Attack* thisAttack = aliveAttacks.at(i).get();
			thisAttack->pos = this->pos + (this->facingLeft ? sf::Vector2f(35,-4) : sf::Vector2f(-4,-4));
			thisAttack->body.left = this->body.left + (this->facingLeft ? -22 : 22);
			thisAttack->body.top = this->body.top+12;
			thisAttack->render(screen);

			sf::RectangleShape r;
			r.setSize(sf::Vector2f(32,32));
			r.setPosition(thisAttack->body.left, thisAttack->body.top);
			//screen.draw(r);
		}
	} else {
		sf::Vector2f pos = this->pos + (this->facingLeft ? sf::Vector2f(35,-4) : sf::Vector2f(-4,-4));
		this->sSpr.setPosition(pos);
		if(currentAnim != IDLE){
			this->sSpr.setTextureRect(sf::IntRect(32,0,32,32));
		} else {
			this->sSpr.setTextureRect(sf::IntRect(0,0,32,32));
		}
		screen.draw(this->sSpr);
	}
}

bool Player::onHit(int damage, bool facingLeft){
	this->HP -= damage;
	/*if (HP <= 0) {
		for (int i = 0; i < this->aliveAttacks.size(); i++) {
			Attack* thisAttack = aliveAttacks.at(i).get();
			thisAttack->dead = true;
		}
	}*/
	vel.x += (facingLeft ? -150 : 150);
	if (invulnWindow < 0) {
		invulnWindow = 0.5;
	}
	return true;
}
