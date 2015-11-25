#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "Actor.hpp"
#include <cstdlib>

namespace lava
{
	class Platform : public Actor
	{
	private:
		sf::Sprite platformSprite;
		float vx;
		int platformWidth;

	public:
		Platform(int x, int y, int width, sf::Texture* platformTexture);

		void update(float delta);
		void render(sf::RenderWindow* window);
		float getX() { return platformSprite.getPosition().x; }
		float getY() { return platformSprite.getPosition().y; }
		sf::Sprite getSprite(){ return platformSprite; }
		float getVelocityX() { return vx; }
	};
}

#endif