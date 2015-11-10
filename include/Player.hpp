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
		sf::RectangleShape rect;
		float charge;
		bool landed;

		static const int A = 1100;
		static const int MINJUMP = 200;
		static const int MAXJUMP = 1000;
<<<<<<< HEAD
=======
		static const int VX = 200;
>>>>>>> bfb757572dd4fe2689868ca2ffe888e0b9599ca8
		
	public:
		Player();
		
		void update(float delta);
		void render(sf::RenderWindow* window);
		void jump();
<<<<<<< HEAD
=======
		void die();
>>>>>>> bfb757572dd4fe2689868ca2ffe888e0b9599ca8
		void land(float y);
		bool charging;
		bool moveLeft;
		bool moveRight;
		bool isFalling() { return vy > 0; }
<<<<<<< HEAD
=======
		bool alive;
>>>>>>> bfb757572dd4fe2689868ca2ffe888e0b9599ca8
		
		float getX() { return rect.getPosition().x; }
		float getY() { return rect.getPosition().y; }
		sf::RectangleShape getRect() { return rect; }
	};
}

#endif