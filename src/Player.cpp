#include "Player.hpp"
#include <iostream>

namespace lava
{
	Player::Player():
	rect(sf::Vector2f(20, 40)),
	vx(0),
	vy(0),
	charge(false),
	charging(false),
	moveLeft(false),
	moveRight(false),
	landed(true)
	{
		// test start position
		rect.setPosition(550, 550);
	}
	
	void Player::update(float delta)
	{
		// update charge
		if (charging) charge += delta;
		
		// don't leave level
		if (this->getY() > 560) {
			land(600);
		}
		
		// if not landed, fall
		if (!landed) {
			vy += A * delta;
		}
		
		// left and right movement, only move in air
		vx = 0;
		if (vy != 0)
		{
			if (moveLeft && moveRight) vx = 0;
			else if (moveLeft) vx = 200;
			else if (moveRight) vx = -200;
			else vx = 0;
		}
		
		// move player
		rect.move(delta * vx, delta * vy);
	}
	
	void Player::render(sf::RenderWindow* window)
	{
		window->draw(rect);
	}
	
	void Player::jump()
	{
		if (vy == 0) {
			// TODO: non-linear function for charging power?
			float dvy = 2 * charge * 600;

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
			rect.setPosition(this->getX(), y - this->getRect().getSize().y);
			landed = true;
		}
	}
}