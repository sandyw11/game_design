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
		Platform(int height, int width);
	
		void update(float delta);
		void render(sf::RenderWindow* window);
		float getX() {}
		float getY() {}
		float getWidth() { return rect.getSize().x; }
		float getHeight() { return rect.getSize().y; }
	};
}

#endif