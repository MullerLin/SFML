#include "Enemy.h"

Enemy::Enemy(Texture *texture, Vector2u windowSize)
{
	
	this->HPMax = rand() % 3 + 1;
	this->HP = HPMax;

	this->shape.setTexture(*texture);

	this->shape.setScale(0.1f, 0.1f);
	
	this->range = windowSize.y - this->shape.getGlobalBounds().height;

	this->shape.setPosition(windowSize.x, rand()%this->range);

}

Enemy::~Enemy(){}