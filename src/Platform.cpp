#include "Platform.hpp"

namespace lava
{
	Platform::Platform(int x, int y, int width, sf::Texture* platformTexture) //:
	//rect(sf::Vector2f(width, 10))
	{
		//rect.setPosition(x, y);
		platformSprite.setTexture(*platformTexture);
		platformSprite.setTextureRect(sf::IntRect(0, 0, width, 15));
		platformSprite.setPosition(x,y);
		platformSprite.setScale(1, 1.5f); 
	}
	
	void Platform::update(float delta)
	{
		// movement?
	}
	
	void Platform::render(sf::RenderWindow* window)
	{
		//window->draw(rect);
		window->draw(platformSprite);
	}
}