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
		float vy;
		int platformWidth;
		
		bool fallingPlatform;
		float fallTime;
		bool fallStarted;

		static const int FALL_TIME = 2;
		static const int MIN_VX = 100;
		static const int MAX_VX = 150;

	public:
		Platform(int x, int y, int width, sf::Texture* platformTexture);

		void update(float delta);
		void render(sf::RenderWindow* window);

		float getX() { return platformSprite.getPosition().x; }
		float getY() { return platformSprite.getPosition().y; }
		sf::Sprite getSprite(){ return platformSprite; }

		float getVelocityX() { return vx; }
		float getVelocityY() { return vy; }

		bool isFallingPlatform() { return fallingPlatform; }
		void startFall();
	};
}

#endif