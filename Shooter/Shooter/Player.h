#pragma once
#include "Bullet.h"

class Player
{
public:
	Sprite shape;
	Texture* texture;

	int HP;
	int HPMax;
	int shootTimer;

	std::vector<Bullet> bullets;

	Player(Texture *texture, int _shooterTime);
	
	~Player();
};
