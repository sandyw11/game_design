#include "Player.hpp"
#include <iostream>
<<<<<<< HEAD
=======
#include <cmath>
>>>>>>> bfb757572dd4fe2689868ca2ffe888e0b9599ca8

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
<<<<<<< HEAD
	landed(true)
=======
	landed(true),
	alive(true)
>>>>>>> bfb757572dd4fe2689868ca2ffe888e0b9599ca8
	{
		// test start position
		rect.setPosition(400, 50000);
	}
	
	void Player::update(float delta)
	{
<<<<<<< HEAD
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
=======
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
			rect.move(delta * vx, delta * vy);
		}
>>>>>>> bfb757572dd4fe2689868ca2ffe888e0b9599ca8
	}
	
	void Player::render(sf::RenderWindow* window)
	{
		window->draw(rect);
	}
	
	void Player::jump()
	{
		if (vy == 0) {
<<<<<<< HEAD
			// TODO: non-linear function for charging power?
			float dvy = 2 * charge * 600;
=======
			// TODO: non-linear function for charging power? sqrt?
			float dvy = std::sqrt(charge) * 720;
			std::cout << "charge: " << charge << ", dvy: " << dvy << "\n";
>>>>>>> bfb757572dd4fe2689868ca2ffe888e0b9599ca8

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
<<<<<<< HEAD
=======
	}

	void Player::die()
	{
		vy = 0;
		vy = 0;
		alive = false;
>>>>>>> bfb757572dd4fe2689868ca2ffe888e0b9599ca8
	}
}