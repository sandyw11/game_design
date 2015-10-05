#include "Player.hpp"

namespace lava
{
	Player::Player():
	rect(sf::Vector2f(50, 50)),
	vx(0),
	vy(0)
	{
		// test start position
		rect.setPosition(550, 550);
	}
	
	void Player::update(float delta)
	{
		rect.move(delta * vx, delta * vy);
	}
	
	void Player::render(sf::RenderWindow* window)
	{
		window->draw(rect);
	}
}