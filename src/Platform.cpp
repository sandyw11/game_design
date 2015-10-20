#include "Platform.hpp"

namespace lava
{
	Platform::Platform(int x, int y):
	rect(sf::Vector2f(100, 10))
	{
		rect.setPosition(x, y);
	}
	
	void Platform::update(float delta)
	{
		// movement?
	}
	
	void Platform::render(sf::RenderWindow* window)
	{
		window->draw(rect);
	}
}