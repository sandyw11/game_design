#include "Powerup.hpp"

namespace lava
{
	Powerup::Powerup(int x, int y):
	time(START_TIME),
	active(false),
	rect(sf::Vector2f(WIDTH, HEIGHT))
	{
		rect.setPosition(sf::Vector2f(x, y));
	}

	void Powerup::update(float delta)
	{
		// TODO: don't need to do anything... unless we want movement
		if (active)
		{
			time -= delta;
		}
	}

	void Powerup::render(sf::RenderWindow* window)
	{
		window->draw(rect);
	}
}