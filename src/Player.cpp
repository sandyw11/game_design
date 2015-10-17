#include "Player.hpp"
#include <iostream>
#include <iomanip>

namespace lava
{
	Player::Player():
	rect(sf::Vector2f(50, 50)),
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
		if (rect.getPosition().y > 550){
			vy = 0;
			rect.setPosition(rect.getPosition().x, 550);
		} else if (rect.getPosition().y != 550) {
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
		std::cout << "Jump!\n";
		float dvy = 2 * charge * 600;
		
		if (dvy > MAXJUMP) dvy = MAXJUMP;
		if (dvy < MINJUMP) dvy = MINJUMP;
		
		vy -= dvy;
		
		std::cout << charge;
		charge = 0;
	}
}