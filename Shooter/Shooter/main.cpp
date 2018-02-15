#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"

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
	int shootTimer = 20;


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

		// Player restrain in the window
		if (player.shape.getPosition().x <= 0)                                                                                  // Left
			player.shape.setPosition(0.f, player.shape.getPosition().y);

		if (player.shape.getPosition().x  >= window.getSize().x - player.shape.getGlobalBounds().width)
			player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);  // Right

		if (player.shape.getPosition().y <= 0)
			player.shape.setPosition(player.shape.getPosition().x, 0.f);                                                        // Up

		if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height)
			player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height); // Down


		// Update controls
		if (shootTimer < 20)
			shootTimer++;

		if (Keyboard::isKeyPressed(Keyboard::K) && shootTimer >= 20)
		{
			Vector2f offset(10.f, 20.f);
			player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition() + offset));
			shootTimer = 0; // Reset timer
		}
		
		// Bullets
		

		
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
 			// Move 
			player.bullets[i].shape.move(20.f, 0.f);

			// Out of window bounds
			if (player.bullets[i].shape.getPosition().x >= window.getSize().x)
				player.bullets.erase(player.bullets.begin());
		}

		// Enemy collison

		// Update enemy

		// Draw
		window.clear();
		
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
			window.draw(player.bullets[i].shape);
		}

		window.draw(player.shape);

		window.display();
	}

	return 0;
}