#pragma once
#include "Bullet.h"

class Player
{
public:
	Sprite shape;
	Texture* texture;

	int HP;
	int HPMax;

	std::vector<Bullet> bullets;

	Player(Texture *texture);
	
	~Player();
};
