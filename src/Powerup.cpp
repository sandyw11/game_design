#include "Powerup.hpp"

namespace lava
{
	Powerup::Powerup(int x, int y, int type, sf::Texture *powerupTexture):
	time(START_TIME),
	active(false)
	{
		chosentype = PowerupType(type);
		powerupSprite.setTexture(*powerupTexture);
		if (chosentype == 0){
			powerupSprite.setPosition(x, y - 20);
			powerupSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
			powerupSprite.setScale(2.0f, 2.0f);
		}
		else if (chosentype == 1){
			powerupSprite.setPosition(x, y - 20);
			powerupSprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
			powerupSprite.setScale(2.0f, 2.0f);
		}
		else if (chosentype == 2){
			powerupSprite.setPosition(x, y - 20);
			powerupSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
			powerupSprite.setScale(1.5f, 1.5f);
		}
		else{
			std::cout << "Unknown Powerup" << std::endl;
		}
		// TODO: different sprite for different powerups
		// for video: always pick up jetpack
		//type = PowerupType::JETPACK;
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
