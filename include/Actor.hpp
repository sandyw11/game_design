#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <SFML/Graphics.hpp>

namespace lava
{
	class Actor
	{	
	public:
		virtual void update(float delta) {}
		virtual void render(sf::RenderWindow* window) {}
		virtual float getX() {}
		virtual float getY() {}
	};
}

#endif