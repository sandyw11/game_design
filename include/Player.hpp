#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Actor.hpp"
#include "GameOverEvent.hpp"
#include "EventManager.hpp"
#include "Platform.hpp"
#include <ctime>

namespace lava
{
	class Player : public Actor
	{
	private:
		float vx;
		float vy;
		sf::Texture playerTexture;
		sf::Sprite playerSprite; 
		sf::Clock clock;
		float charge;

		static const int MINJUMP = 200;
		static const int MAXJUMP = 1000;
		static const int VX = 200;
		
	public:
		Player(sf::Texture *playerTexture, lava::eventManager *manager);
		
		void update(float delta);
		void stickToPlatform(float delta, float vx, float vy);
		void render(sf::RenderWindow* window);
		void jump();
		void die();
		void land(float y);
		void hitByRock(float rockVy);
		void applyPowerup(int type);
		float getCharge();
		bool charging;
		bool moveLeft;
		bool moveRight;
		bool isFalling() { return vy > 0; }
		bool faceLeft;
		
		int score; 
		bool alive;
		bool landed;
		const char* powerup;
		float powerupTime;

		float getX() { return playerSprite.getPosition().x; }
		float getY() { return playerSprite.getPosition().y; }
		const char* getPowerup() { return powerup; }
		sf::Sprite getSprite() { return playerSprite; }
		void resetPosition();
	};
}

#endif
