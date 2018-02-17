#include "Player.h"



Player::Player(Texture *texture, int _shootTimer)
{
	{
		this->HPMax = 10;
		this->HP = this->HPMax;

		this->shootTimer = _shootTimer;

		this->texture = texture;
		this->shape.setTexture(*texture);

		this->shape.setScale(0.1f, 0.1f);

	}

}


Player::~Player()
{
}
