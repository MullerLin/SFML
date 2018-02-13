#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <math.h>
#include <cstdlib>
#include <vector>

using namespace sf;

class Bullet
{
public:
	Sprite shape;
	Bullet(Texture *texture)
	{
		this->shape.setTexture(*texture);

		this->shape.setScale(0.3f, 0.3f);
	}

	~Bullet() {}
};

class Player
{
public:
	Sprite shape;
	Texture* texture;

	int HP;
	int HPMax;
	
	std::vector<Bullet> bullets;

	Player(Texture *texture)
	{
		this->HPMax = 10;
		this->HP = this->HPMax;
		
		this->texture = texture;
		this->shape.setTexture(*texture);

		this->shape.setScale(0.1f, 0.1f);
	}
	~Player() {}
};


class Enemy
{
public:

};



int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(800, 600), "Space Shooter", Style::Default);

	window.setFramerateLimit(60);

	// Init text
	Font font;
	font.loadFromFile("Fonts/Dosis-Light.ttf");

	// Init textures
	Texture playerTex;
	playerTex.loadFromFile("Textures/ship.png");

	Texture enemyTex;
	enemyTex.loadFromFile("Textures/enemy.png");

	Texture bulletTex;
	enemyTex.loadFromFile("Textures/missileTex01.png");

	// Player init
	Player player(&playerTex);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		// Upadte Shooting
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			player.bullets.push_back(Bullet(&bulletTex));
		}
		
		// Draw
		window.clear();
		
		
		window.draw(player.shape);
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
			window.draw(player.bullets[i].shape);
		}

		window.display();
	}

	return 0;
}