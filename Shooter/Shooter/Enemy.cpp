#include "Enemy.h"

Enemy::Enemy(Texture *texture, Vector2u windowSize)
{
	
	this->HPMax = rand()%2 + 1;
	this->HP = HPMax;

	this->shape.setTexture(*texture);

	this->shape.setScale(1.f, 1.f);
	
	this->range = windowSize.y - this->shape.getGlobalBounds().height;

	this->shape.setPosition(windowSize.x, rand()%this->range);

}

Enemy::~Enemy(){}