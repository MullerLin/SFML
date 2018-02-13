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

		this->shape.setScale(0.07f, 0.07f);
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
	bulletTex.loadFromFile("Textures/missileTex01.png");

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

		// Upadte 
		
		// Update player
		if (Keyboard::isKeyPressed(Keyboard::W))
			player.shape.move(0.f, -10.f);

		if (Keyboard::isKeyPressed(Keyboard::S))
			player.shape.move(0.f, 10.f);

		if (Keyboard::isKeyPressed(Keyboard::A))
			player.shape.move(-10.f, 0.f);

		if (Keyboard::isKeyPressed(Keyboard::D))
			player.shape.move(10.f, 0.f);


		// Update controls
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			player.bullets.push_back(Bullet(&bulletTex));
		}
		
		// Bullets
		// Out of window bounds
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
 			if (player.bullets[i].shape.getPosition().x >= window.getSize().x)
				player.bullets.erase(player.bullets.begin());
		}

		// Enemy collison

		// Update enemy

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