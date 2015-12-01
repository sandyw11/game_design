#include "Player.hpp"
#include "GameLogic.hpp"
#include <iostream>
#include <cmath>

namespace lava
{
	Player::Player(sf::Texture* playerTexture, lava::eventManager* manager):
	vx(0),
	vy(0),
	powerupTime(0),
	charge(false),
	charging(false),
	moveLeft(false),
	moveRight(false),
	landed(true),
	alive(true)
	{
		score = 0;
		playerSprite.setTexture(*playerTexture);
		playerSprite.setTextureRect(sf::IntRect(0,0,32,32));
		playerSprite.setScale(1.5f,1.5f);
		playerSprite.setPosition(400, GameLogic::START_Y - 5);
	}
	
	void Player::update(float delta)
	{
		if (alive)
		{
			if (playerSprite.getPosition().x > 800)
			{
				playerSprite.setPosition(0, playerSprite.getPosition().y);
			}
			else if (playerSprite.getPosition().x < 0)
			{
				playerSprite.setPosition(800, playerSprite.getPosition().y);
			}
			// update charge
			if (charging) 
			{
				charge += delta;
				if (!faceLeft)
				{
					playerSprite.setTextureRect(sf::IntRect(32, 64, 32, 32));
					playerSprite.setScale(1.5f, 1.5f);
				}
				else
				{
					playerSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
					playerSprite.setScale(1.5f, 1.5f);
				}
			}
			else 
			{
				if (!faceLeft)
				{
					playerSprite.setTextureRect(sf::IntRect(64, 64, 32, 32));
					playerSprite.setScale(1.5f, 1.5f);
				}
				else
				{
					playerSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
					playerSprite.setScale(1.5f, 1.5f);
				}
			}

			// if not landed, fall
			if (!landed) 
			{
				if (!charging)
				{
					if (!faceLeft)
					{
						if (powerup == "JETPACK")
						{
							playerSprite.setTextureRect(sf::IntRect(64, 32, 32, 32));
							playerSprite.setScale(1.5f, 1.5f);
						}
						else
						{
							playerSprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
							playerSprite.setScale(1.5f, 1.5f);
						}
					}
					else
					{
						if (powerup == "JETPACK")
						{
							playerSprite.setTextureRect(sf::IntRect(96, 32, 32, 32));
							playerSprite.setScale(1.5f, 1.5f);
						}
						else
						{
							playerSprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
							playerSprite.setScale(1.5f, 1.5f);
						}

					}
				}
				vy += GameLogic::A * delta;
			}

			// left and right movement, only move in air
			vx = 0;
			if (vy != 0)
			{
				if (moveLeft && moveRight) vx = 0;
				else if (moveLeft){
					vx = VX;
					if (!charging)
					{
						if (powerup == "JETPACK")
						{
							playerSprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
							playerSprite.setScale(1.5f, 1.5f);
						}
						else
						{
							playerSprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
							playerSprite.setScale(1.5f, 1.5f);
						}
					}
				}
				else if (moveRight)
				{
					vx = -VX;
					if (!charging)
					{
						if (powerup == "JETPACK")
						{
							playerSprite.setTextureRect(sf::IntRect(32, 32, 32, 32));
							playerSprite.setScale(1.5f, 1.5f);
						}
						else
						{
							playerSprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
							playerSprite.setScale(1.5f, 1.5f);
						}
					}
				}
				else vx = 0;
			}

			// move player
			playerSprite.move(delta * vx, delta * vy);
		}
	}
	
	void Player::render(sf::RenderWindow* window)
	{
		window->draw(playerSprite);
	}
	
	void Player::jump()
	{
		if (vy == 0) {
			// non-linear function for charging power, sqrt
			float dvy = std::sqrt(charge) * 720;

			if (faceLeft){
				playerSprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
				playerSprite.setScale(1.5f, 1.5f);
			}
			else {
				playerSprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
				playerSprite.setScale(1.5f, 1.5f);
			}

			// filter for min and max
			if (dvy > MAXJUMP) dvy = MAXJUMP;
			if (dvy < MINJUMP) dvy = MINJUMP;

			vy -= dvy;

			charge = 0;
			landed = false;
		}
	}

	void Player::land(float y)
	{
		if (vy > 0)
		{
			vy = 0;
			if (score < GameLogic::START_Y - playerSprite.getPosition().y){
				score = GameLogic::START_Y - playerSprite.getPosition().y;
			}
			//playerSprite.setPosition(this->getX(), y - this->getSprite().getSize().y);
			playerSprite.setPosition(this->getX(), y - this->getSprite().getGlobalBounds().height);
			landed = true;

			if (faceLeft){
				playerSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
				playerSprite.setScale(1.5f, 1.5f);
			}
			else{
				playerSprite.setTextureRect(sf::IntRect(64, 64, 32, 32));
				playerSprite.setScale(1.5f, 1.5f);
			}
		}
	}

	void Player::stickToPlatform(float delta, float vx, float vy)
	{
		playerSprite.move(delta * vx, delta * vy);
	}

	void Player::hitByRock(float rockVy)
	{
		// push player down
		vy += rockVy / 2;
		landed = false;
	}

	void Player::applyPowerup(int type)
	{
		if (type == 0)
		{
			powerup = "JETPACK";
		}
		else
		{
			powerup = "SHIELD";
		}
	}

	void Player::die()
	{
		vy = 0;
		vy = 0;
		alive = false;
	}
	
	float Player::getCharge()
	{
	    return charge;
	}

	void Player::resetPosition()
	{
		vx = 0;
		vy = 0;
		playerSprite.setPosition(400, GameLogic::START_Y - 5);
	}
}
