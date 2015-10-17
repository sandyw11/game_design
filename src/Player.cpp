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
	charging(false)
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
		
		// move player
		rect.move(delta * vx, delta * vy);
	}
	
	void Player::render(sf::RenderWindow* window)
	{
		window->draw(rect);
	}
	
	void Player::jump()
	{
		float dvy = 2 * charge * 600;
		
		if (dvy > MAXJUMP) dvy = MAXJUMP;
		if (dvy < MINJUMP) dvy = MINJUMP;
		
		vy -= dvy;
		
		charge = 0;
	}
}