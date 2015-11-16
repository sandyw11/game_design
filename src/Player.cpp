#include "Player.hpp"
#include <iostream>
#include <cmath>

namespace lava
{
	Player::Player():
	//rect(sf::Vector2f(20, 40)),
	vx(0),
	vy(0),
	charge(false),
	charging(false),
	moveLeft(false),
	moveRight(false),
	landed(true),
	alive(true)
	{
		// test start position
		//rect.setPosition(400, 50000);
		if (!playerTexture.loadFromFile("Guy.png"))
		{
			std::cout << "WHY NO LOAD" << std::endl;
		}
		playerSprite.setTexture(playerTexture);
		playerSprite.setTextureRect(sf::IntRect(0,0,32,32));
		playerSprite.setPosition(400, 50000);
		std::cout << playerSprite.getTextureRect().height << std::endl;
		playerSprite.setScale(1.5f,1.5f);
		std::cout << playerSprite.getGlobalBounds().height << std::endl;
	}
	
	void Player::update(float delta)
	{
		if (alive)
		{
			// update charge
			if (charging) charge += delta;

			// if not landed, fall
			if (!landed) {
				vy += A * delta;
			}

			// left and right movement, only move in air
			vx = 0;
			if (vy != 0)
			{
				if (moveLeft && moveRight) vx = 0;
				else if (moveLeft) vx = VX;
				else if (moveRight) vx = -VX;
				else vx = 0;
			}

			// move player
			playerSprite.move(delta * vx, delta * vy);
		}
	}
	
	void Player::render(sf::RenderWindow* window)
	{
		//window->draw(rect);
		window->draw(playerSprite);
	}
	
	void Player::jump()
	{
		if (vy == 0) {
			// TODO: non-linear function for charging power? sqrt?
			float dvy = std::sqrt(charge) * 720;
			std::cout << "charge: " << charge << ", dvy: " << dvy << "\n";

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
			//playerSprite.setPosition(this->getX(), y - this->getSprite().getSize().y);
			playerSprite.setPosition(this->getX(), y - this->getSprite().getGlobalBounds().height);
			landed = true;
		}
	}

	void Player::die()
	{
		vy = 0;
		vy = 0;
		alive = false;
	}
}