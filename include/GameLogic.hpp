#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <vector>
#include "Player.hpp"

namespace lava
{
	class GameLogic
	{
	public:
		enum GameState
		{
			PLAY,
			PAUSE,
			GAME_OVER
		};
		void update(float delta);
		GameLogic();
		
	private:
		GameState gameState;
		
		std::vector<lava::Actor*> actors;
		Player player;
	};
}

#endif