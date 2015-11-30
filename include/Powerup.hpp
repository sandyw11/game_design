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
		Powerup(int x, int y);
		~Powerup();

		const static int WIDTH = 20;
		const static int HEIGHT = 20;

		void update(float delta);
		void render(sf::RenderWindow* window);
		enum PowerupType { JETPACK, HIGHJUMP };

		float getTime() { return time; }
		float getX() { return rect.getPosition().x; }
		float getY() { return rect.getPosition().y; }

		sf::RectangleShape getRect() { return rect; }
		PowerupType getType() { return type; }

	private:
		sf::RectangleShape rect;
		PowerupType type;

		const static int START_TIME = 20;

		float time;
		bool active;
	};
}

#endif
