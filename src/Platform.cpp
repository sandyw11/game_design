#include "Platform.hpp"
#include "GameLogic.hpp"
#include "Random.hpp"

namespace lava
{
	Platform::Platform(int x, int y, int width, sf::Texture* platformTexture) :
	vx(0),
	vy(0),
	fallingPlatform(false),
	fallStarted(false),
	platformWidth(width)
	{
		platformSprite.setTexture(*platformTexture);
		platformSprite.setTextureRect(sf::IntRect(0, 0, width, 15));
		platformSprite.setPosition(x,y);
		platformSprite.setScale(1, 1.5f); 

		// random chance of being a moving platform
		int platformType = rand() % 10;
		if (platformType == 0)
		{
			vx = Equilikely(MIN_VX, MAX_VX);
		}
		else
		{
			fallingPlatform = true;
			fallTime = FALL_TIME;
		}
	}
	
	void Platform::update(float delta)
	{
		// check bounds
		if (vx != 0 && getX() + platformWidth > 800 || getX() < 0)
		{
			vx *= -1;

			// fix stuck bug
			if (getX() < 0) platformSprite.setPosition(sf::Vector2f(0, getY()));
			if (getX() + platformWidth > 800) platformSprite.setPosition(sf::Vector2f(800 - platformWidth, getY()));
		}

		// move platform
		platformSprite.move(delta * vx, delta * vy);

		// falling platform timer
		if (fallingPlatform && fallStarted)
		{
			if (fallTime > 0)
			{
				fallTime -= delta;
			}
			else if (fallTime < 0)
			{
				fallTime = 0;
			}
			else {
				vy += GameLogic::A * delta;
			}
		}
	}

	void Platform::startFall()
	{
		if (fallingPlatform) fallStarted = true;
	}
	
	void Platform::render(sf::RenderWindow* window)
	{
		window->draw(platformSprite);
	}
}