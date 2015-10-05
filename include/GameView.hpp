#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <vector>
#include "Actor.hpp"

namespace lava
{
	class GameView
	{
	public:
		void update(float delta);
		void processIntput();
		GameView();
		
	protected:
		sf::RenderWindow window;
	};
}

#endif