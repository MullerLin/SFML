#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"

int main()
{
	// Generate random seed
	srand(time(NULL));
	
	RenderWindow window(VideoMode(800, 600), "Space Shooter", Style::Default);

	window.setFramerateLimit(60);

	// Init globals
	const int SPAWNLAPSE = 90;
	const int SHOOTLAPSE = 20;
	const float ENEMY_SPEED = 4.5f;
	const int COLLIDE_DAMAGE = 2;

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
	Player player(&playerTex, SHOOTLAPSE);

	// Enemy init
	int enemySpawnTimer = 0;
	std::vector<Enemy> enemies;
	enemies.push_back(Enemy(&enemyTex, window.getSize()));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		// Print Hp on the console(used for debugging)
		std::cout << player.HP << std::endl;
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
		if (player.shootTimer < SHOOTLAPSE)
		{
			player.shootTimer++;
		}
		if (Keyboard::isKeyPressed(Keyboard::K) && player.shootTimer >= SHOOTLAPSE)
		{
			Vector2f offset(10.f, 20.f);
			player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition() + offset));
			player.shootTimer = 0; // Reset timer
		}
		
		// Bullets
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
 			// Move 
			player.bullets[i].shape.move(20.f, 0.f);

			// Out of window bounds
			if (player.bullets[i].shape.getPosition().x >= window.getSize().x)
			{
				player.bullets.erase(player.bullets.begin() + i);
				break;
			}
			// Enemy collison
			for (size_t k = 0; k < enemies.size(); k++)
			{
				if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
				{
					enemies.erase(enemies.begin() + k);
					player.bullets.erase(player.bullets.begin() + i);
					break;
				}
			}
		}


		// Update enemies
		if (enemySpawnTimer < SPAWNLAPSE)
		{
			enemySpawnTimer++;
		}

		// Spawn timer
		if (enemySpawnTimer >= SPAWNLAPSE)
		{
			enemies.push_back(Enemy(&enemyTex, window.getSize()));
			enemySpawnTimer = 0;
		}

		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].shape.move(-ENEMY_SPEED, 0);
			
			if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width)
			{
				enemies.erase(enemies.begin() + i);
			}

			if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
			{
				enemies.erase(enemies.begin() + i);
				// Player take damage
				player.HP -= COLLIDE_DAMAGE;
			}
		}

		// Draw
		window.clear();
		
		// Bullets
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
			window.draw(player.bullets[i].shape);
		}

		// Player
		window.draw(player.shape);

		// Render enemies
		for (size_t i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i].shape);
		}

		window.display();
	}

	return 0;
}