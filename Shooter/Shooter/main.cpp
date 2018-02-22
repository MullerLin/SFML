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
	int SPAWNLAPSE = 90;
	const int SHOOTLAPSE = 10;
	float ENEMY_SPEED = 4.5f;
	const int COLLIDE_DAMAGE = 1;
	float PlayerSpeed = 10.f;
	int playerScore = 0;
	bool gameIsOver = true;
	Vector2f initPos(0.f, 45.f);

	// Init font
	Font font;
	font.loadFromFile("Fonts/Dosis-Light.ttf");

	// Init audio
	Music background;
	background.openFromFile("Audio/Electrix_NES.ogg");
	
	SoundBuffer welcomeBuffer;
	welcomeBuffer.loadFromFile("Audio/welcome.ogg");
	Sound welcomeSound(welcomeBuffer);
	welcomeSound.setVolume(100.f);

	// Play BGM
	background.play();
	background.setVolume(10.f);
	background.setLoop(true);

	// Init textures
	Texture playerTex;
	playerTex.loadFromFile("Textures/ship.png");

	Texture enemyTex;
	enemyTex.loadFromFile("Textures/enemy.png");

	Texture bulletTex;
	bulletTex.loadFromFile("Textures/missileTex01.png");

	// Score UI init
	Text score;
	score.setFont(font);
	score.setCharacterSize(20);
	score.setFillColor(Color::White);
	score.setPosition(10.f, 10.f);

	// Game status UI
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(30);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition(window.getSize().x / 2 - 200, 
							 window.getSize().y / 2 - gameOverText.getGlobalBounds().height / 2);
	gameOverText.setString("WELCOME TO SPACE SHOOTER!!\n          PRESS SPACE TO START\n\n          made by Charlie");
	

	// Player init
	Player player(&playerTex, SHOOTLAPSE);
	player.shape.setPosition(initPos);
	
	Text hpText;
	hpText.setFont(font);
	hpText.setCharacterSize(12);
	hpText.setFillColor(Color::White);

	// Enemy init
	int enemySpawnTimer = 0;
	std::vector<Enemy> enemies;
	enemies.push_back(Enemy(&enemyTex, window.getSize()));
	// Enemy text
	Text ehpText;
	ehpText.setFont(font);
	ehpText.setCharacterSize(13);
	ehpText.setFillColor(Color::White);


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			{
				window.close();
				break;
			}
			if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Space))
			{
				if (gameIsOver)
				{
					// Play sound
					welcomeSound.play();

					// Restart game
					gameIsOver = false;

					// Reset score
					playerScore = 0;

					// Reset player health
					player.HP = player.HPMax;

					// Reset game config
					ENEMY_SPEED = 4.5f;
					PlayerSpeed = 10.f;
					background.setVolume(10.f);
					SPAWNLAPSE = 90;

					// Reset player position
					player.shape.setPosition(initPos);

				}
			}
		}
		
		


		
		// Upadte 
		
		// Update player
		if (!gameIsOver)
		{
			if (Keyboard::isKeyPressed(Keyboard::W))
				player.shape.move(0.f, -PlayerSpeed);

			if (Keyboard::isKeyPressed(Keyboard::S))
				player.shape.move(0.f, PlayerSpeed);

			if (Keyboard::isKeyPressed(Keyboard::A))
				player.shape.move(-PlayerSpeed, 0.f);

			if (Keyboard::isKeyPressed(Keyboard::D))
				player.shape.move(PlayerSpeed, 0.f);

			hpText.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpText.getGlobalBounds().height - 3); // Move up 3
			hpText.setString("HP: " + std::to_string(player.HP) + "/" + std::to_string(player.HPMax));

			// Player restrain in the window
			if (player.shape.getPosition().x <= 0)                                                                                  // Left
				player.shape.setPosition(0.f, player.shape.getPosition().y);

			if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width)
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
						enemies[k].HP--;
						if (!gameIsOver)
							playerScore += 5;

						if (ENEMY_SPEED < 15.0f)
							ENEMY_SPEED += 0.1f;

						if (SPAWNLAPSE >= 15)
							SPAWNLAPSE -= 1;

						if (enemies[k].HP <= 0)
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
				if (!gameIsOver)
					enemies.push_back(Enemy(&enemyTex, window.getSize()));
				enemySpawnTimer = 0;
			}

			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i].shape.move(-ENEMY_SPEED, 0);

				if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width)
				{
					enemies.erase(enemies.begin() + i);
					break;
				}

				if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					enemies.erase(enemies.begin() + i);
					// Player take damage
					player.HP -= COLLIDE_DAMAGE;
					if (ENEMY_SPEED >= 10.3f)
						ENEMY_SPEED -= 6.0f;
					if (SPAWNLAPSE <= 85)
						SPAWNLAPSE += 5;
					break;
				}
			}
		}

		// Update score
		score.setString("SCORE: " + std::to_string(playerScore));

		// ################Draw ##########################################################
		window.clear();
		
		// Bullets
		if (!gameIsOver)
		{
			for (size_t i = 0; i < player.bullets.size(); i++)
			{
				window.draw(player.bullets[i].shape);
			}
		}

		// Player
		window.draw(player.shape);
		if (player.HP == 0)
		{
			gameOverText.setString("GAME OVER\nSCORE: " + std::to_string(playerScore) +
				"\nPress space to restart or\nescape to exit");
			gameIsOver = true;
		}
		// Render enemies
		if (!gameIsOver)
		{
			for (size_t i = 0; i < enemies.size(); i++)
			{
				ehpText.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y - hpText.getGlobalBounds().height);
				ehpText.setString("HP: " + std::to_string(enemies[i].HP) + "/" + std::to_string(enemies[i].HPMax));
				window.draw(ehpText);
				window.draw(enemies[i].shape);
			}
		}

		// Render UI
		window.draw(hpText);
		window.draw(score);
		
		// If game is over (hasn't start or has end)
		if (gameIsOver)
		{
			window.draw(gameOverText);
			ENEMY_SPEED = 0;
			PlayerSpeed = 0;
			gameIsOver = true;
			background.setVolume(5.f);
		}


		window.display();
	}

	return 0;
}