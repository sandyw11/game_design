#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "actor.hpp"

namespace lava
{
	class Player : public Actor
	{
	private:
		float vx;
		float vy;
		sf::RectangleShape rect;
		
	public:
		Player();
		
		void update(float delta);
		void render(sf::RenderWindow* window);
		void jump();
	};
}

#endif