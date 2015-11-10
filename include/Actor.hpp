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
		virtual float getX() { return 0; }
		virtual float getY() { return 0; }
<<<<<<< HEAD
		virtual sf::RectangleShape getRect() {}
=======
>>>>>>> bfb757572dd4fe2689868ca2ffe888e0b9599ca8
	};
}

#endif