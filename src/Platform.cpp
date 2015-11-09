#include "Platform.hpp"

namespace lava
{
	Platform::Platform(int x, int y, int width):
	rect(sf::Vector2f(width, 10))
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