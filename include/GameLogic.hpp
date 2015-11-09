#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <vector>
#include "Level.hpp"
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
		GameLogic(Level* level, Player* player);
		
	private:
		GameState gameState;
		Level* level;
		Player* player;
	};
}

#endif