#pragma once
#include "Bullet.h"	
class Enemy
{
public:
	int HP;
	int HPMax;
	int range;

	Sprite shape;
	
	Enemy(Texture *texture, Vector2u windowSize);
	~Enemy();

};
