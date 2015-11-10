#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <SFML/Graphics.hpp>

namespace lava
{
	class Actor
	{	
	
	public:
		sf::RectangleShape init;
		virtual void update(float delta) {}
		virtual void render(sf::RenderWindow* window) {}
		virtual float getX() { return 0; }
		virtual float getY() { return 0; }
		virtual sf::RectangleShape getRect() { return init; }
	};
}

#endif