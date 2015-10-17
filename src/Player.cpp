#include "Player.hpp"
#include <iostream>
#include <iomanip>

namespace lava
{
	Player::Player():
	rect(sf::Vector2f(20, 40)),
	vx(0),
	vy(0),
	charge(false),
	charging(false),
	moveLeft(false),
	moveRight(false)
	{
		// test start position
		rect.setPosition(550, 550);
	}
	
	void Player::update(float delta)
	{
		// update charge
		if (charging) charge += delta;
		
		// don't leave level
		if (this->getY() > 560){
			vy = 0;
			rect.setPosition(this->getX(), 560);
		} else if (this->getY() != 560) {
			vy += A * delta;
		}
		
		// left and right movement, only move in air
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
		// TODO: non-linear function for charging power?
		float dvy = 2 * charge * 600;
		
		// filter for min and max
		if (dvy > MAXJUMP) dvy = MAXJUMP;
		if (dvy < MINJUMP) dvy = MINJUMP;
		
		vy -= dvy;
		
		charge = 0;
	}
}