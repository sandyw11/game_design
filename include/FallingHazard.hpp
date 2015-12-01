#ifndef FALLING_HAZARD_HPP
#define FALLING_HAZARD_HPP

#include "Actor.hpp"
#include <SFML/Graphics.hpp>

namespace lava
{
	class FallingHazard : public Actor
	{
	private:
		//sf::CircleShape circ;
		sf::Sprite hazardSprite;
		float vx;
		float vy;

	public:
		FallingHazard(int x, int y, int radius,sf::Texture *boulderTexture);

		void update(float delta);
		void render(sf::RenderWindow* window);

		float getX() { return hazardSprite.getPosition().x; }
		float getY() { return hazardSprite.getPosition().y; }
		float getVy() { return vy; }
		//sf::CircleShape getCircle() { return circ; }
		sf::Sprite getCircle(){ return hazardSprite; }
	};
}

#endif
