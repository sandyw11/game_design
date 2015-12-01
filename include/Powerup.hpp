#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "Actor.hpp"
#include "SFML/Graphics.hpp"
#include <cstdlib>

namespace lava
{
	class Powerup : public Actor
	{
	public:
		Powerup(int x, int y, sf::Texture *powerupTexture);
		~Powerup();

		const static int WIDTH = 32;
		const static int HEIGHT = 32;

		void update(float delta);
		void render(sf::RenderWindow* window);
		enum PowerupType { JETPACK, HIGHJUMP };

		float getTime() { return time; }
		float getX() { return powerupSprite.getPosition().x; }
		float getY() { return powerupSprite.getPosition().y; }

		sf::Sprite getSprite() { return powerupSprite; }
		PowerupType getType() { return type; }

	private:
		sf::Sprite powerupSprite;
		PowerupType type;

		const static int START_TIME = 20;

		float time;
		bool active;
	};
}

#endif
