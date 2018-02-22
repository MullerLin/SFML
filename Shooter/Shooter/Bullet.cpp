#include "Bullet.h"

Bullet::Bullet(Texture *texture, Vector2f pos)
{
	this->shape.setTexture(*texture);

	this->shape.setScale(0.07f, 0.07f);
	this->shape.setPosition(pos);
}


Bullet::~Bullet()
{
}
