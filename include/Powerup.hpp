#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "Actor.hpp"
#include "SFML/Graphics.hpp"
#include <cstdlib>
#include <iostream>

namespace lava
{
	class Powerup : public Actor
	{
	public:
		Powerup(int x, int y, int type,sf::Texture *powerupTexture);
		~Powerup();

		const static int WIDTH = 32;
		const static int HEIGHT = 32;

		void update(float delta);
		void render(sf::RenderWindow* window);
		enum PowerupType { JETPACK, LIFEGAIN ,SHIELD,HIGHJUMP };

		float getTime() { return time; }
		float getX() { return powerupSprite.getPosition().x; }
		float getY() { return powerupSprite.getPosition().y; }

		sf::Sprite getSprite() { return powerupSprite; }
		PowerupType getType() { return chosentype; }

	private:
		sf::Sprite powerupSprite;
		PowerupType chosentype;

		const static int START_TIME = 20;

		float time;
		bool active;
	};
}

#endif
