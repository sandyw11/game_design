#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Actor.hpp"
#include "GameOverEvent.hpp"
#include "EventManager.hpp"
#include "Platform.hpp"

namespace lava
{
	class Player : public Actor
	{
	private:
		float vx;
		float vy;
		sf::Texture playerTexture;
		sf::Sprite playerSprite; 
		float charge;

		static const int A = 1100;
		static const int MINJUMP = 200;
		static const int MAXJUMP = 1000;
		static const int VX = 200;
		
	public:
		Player(sf::Texture *playerTexture, lava::eventManager *manager);
		
		void update(float delta);
		void stickToPlatform(float delta, float vx);
		void render(sf::RenderWindow* window);
		void jump();
		void die();
		void land(float y);
		float getCharge();
		bool charging;
		bool moveLeft;
		bool moveRight;
		bool isFalling() { return vy > 0; }
		bool faceLeft;
		
		int score; 
		bool alive;
		bool landed;

		float getX() { return playerSprite.getPosition().x; }
		float getY() { return playerSprite.getPosition().y; }
		sf::Sprite getSprite() { return playerSprite; }
	};
}

#endif