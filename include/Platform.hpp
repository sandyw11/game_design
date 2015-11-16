#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "Actor.hpp"

namespace lava
{
	class Platform : public Actor
	{
	private:
		//sf::RectangleShape rect;
		sf::Sprite platformSprite;

		
	public:
		Platform(int x, int y, int width, sf::Texture* platformTexture);

		void update(float delta);
		void render(sf::RenderWindow* window);
		float getX() { return platformSprite.getPosition().x; }
		float getY() { return platformSprite.getPosition().y; }
		//sf::RectangleShape getRect() { return rect; }
		sf::Sprite getSprite(){ return platformSprite; }
	};
}

#endif