#ifndef FALLING_HAZARD_HPP
#define FALLING_HAZARD_HPP

#include "Actor.hpp"
#include <SFML/Graphics.hpp>

namespace lava
{
	class FallingHazard : public Actor
	{
	private:
		sf::CircleShape circ;
		float vx;
		float vy;

	public:
		FallingHazard(int x, int y, int radius);

		void update(float delta);
		void render(sf::RenderWindow* window);

		float getX() { return circ.getPosition().x; }
		float getY() { return circ.getPosition().y; }
		sf::CircleShape getCircle() { return circ; }
	};
}

#endif
