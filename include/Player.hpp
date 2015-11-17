#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Actor.hpp"

namespace lava
{
	class Player : public Actor
	{
	private:
		float vx;
		float vy;
		//sf::RectangleShape rect;
		sf::Texture playerTexture;
		sf::Sprite playerSprite; 
		float charge;
		bool landed;

		static const int A = 1100;
		static const int MINJUMP = 200;
		static const int MAXJUMP = 1000;
		static const int VX = 200;
		
	public:
		Player(sf::Texture *playerTexture);
		
		void update(float delta);
		void render(sf::RenderWindow* window);
		void jump();
		void die();
		void land(float y);
		bool charging;
		bool moveLeft;
		bool moveRight;
		bool isFalling() { return vy > 0; }
		bool alive;
		bool faceLeft;

		float getX() { return playerSprite.getPosition().x; }
		float getY() { return playerSprite.getPosition().y; }
		//sf::RectangleShape getRect() { return rect; }
		sf::Sprite getSprite() { return playerSprite; }
	};
}

#endif