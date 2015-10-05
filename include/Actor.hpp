#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <SFML/Graphics.hpp>

namespace lava
{
	class Actor
	{
	protected:
		sf::RectangleShape rect;
		
	public:
		virtual void update(float delta) {}
		virtual void render(sf::RenderWindow* window) {}
		sf::RectangleShape getRect() { return rect; }
		float getX() { return rect.getPosition().x; }
		float getY() { return rect.getPosition().y; }
	};
}

#endif