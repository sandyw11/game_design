#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include "Actor.hpp"
#include <SFML/Graphics.hpp>

namespace lava
{
	class Fireball : public Actor
	{
	private:
		//sf::CircleShape circ;
		sf::Sprite hazardSprite;
		float vx;
		float vy;
		float theta;
		float dx;
		float dy;

	public:
		Fireball(double theta, int degree, int y, sf::Texture *fireTexture);

		void update(float delta);
		void render(sf::RenderWindow* window);

		float getX() { return hazardSprite.getPosition().x; }
		float getY() { return hazardSprite.getPosition().y; }
		//sf::CircleShape getCircle() { return circ; }
		sf::Sprite getCircle(){ return hazardSprite; }
	};
}

#endif
