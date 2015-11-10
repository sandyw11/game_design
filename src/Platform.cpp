#include "Platform.hpp"

namespace lava
{
<<<<<<< HEAD
	Platform::Platform(int x, int y):
	rect(sf::Vector2f(100, 10))
=======
	Platform::Platform(int x, int y, int width):
	rect(sf::Vector2f(width, 10))
>>>>>>> bfb757572dd4fe2689868ca2ffe888e0b9599ca8
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