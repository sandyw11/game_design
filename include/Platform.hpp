#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "Actor.hpp"

namespace lava
{
	class Platform : public Actor
	{
	private:
		sf::RectangleShape rect;
		
	public:
		Platform(int x, int y, int width);
	
		void update(float delta);
		void render(sf::RenderWindow* window);
		float getX() { return rect.getPosition().x; }
		float getY() { return rect.getPosition().y; }
		sf::RectangleShape getRect() { return rect; }
	};
}

#endif