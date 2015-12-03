#include "Powerup.hpp"

namespace lava
{
	Powerup::Powerup(int x, int y, sf::Texture *powerupTexture):
	time(START_TIME),
	active(false)
	{
		// TODO: different sprite for different powerups
		powerupSprite.setTexture(*powerupTexture);
		powerupSprite.setPosition(x, y -20);
		powerupSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		powerupSprite.setScale(2.0f, 2.0f);

		// type = PowerupType(rand() % 2);
		// for video: always pick up jetpack
		type = PowerupType::JETPACK;
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
		window->draw(powerupSprite);
	}
}
