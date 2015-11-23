#include "Platform.hpp"

namespace lava
{
	Platform::Platform(int x, int y, int width, sf::Texture* platformTexture):
	vx(0),
	platformWidth(width)
	{
		platformSprite.setTexture(*platformTexture);
		platformSprite.setTextureRect(sf::IntRect(0, 0, width, 15));
		platformSprite.setPosition(x,y);
		platformSprite.setScale(1, 1.5f); 

		// random chance of being a moving platform
		if (rand() % 10 == 0)
		{
			// TODO: not hardcoded
			vx = rand() % 50 + 100;
		}
	}
	
	void Platform::update(float delta)
	{
		// check bounds
		if (getX() + platformWidth > 800 || getX() < 0
			&& vx != 0)
		{
			vx *= -1;
		}

		// move platform
		platformSprite.move(sf::Vector2f(delta * vx, 0));
	}
	
	void Platform::render(sf::RenderWindow* window)
	{
		window->draw(platformSprite);
	}
}