#include "Platform.hpp"

namespace lava
{
	Platform::Platform(int width, int height):
	rect(sf::Vector2f(width, height))
	{
		rect.setPosition(300, 300);
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