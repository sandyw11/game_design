#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <vector>
#include <iostream>
#include "Level.hpp"
#include "Player.hpp"
#include "ActorDestroyedEvent.hpp"
#include "Platform.hpp"

namespace lava
{
	class GameLogic
	{
	public:
		enum GameState
		{
            START,
			PLAY,
			PAUSE,
			GAME_OVER
		};
		void update(float delta);
		GameLogic(Level* level, Player* player);
		void respond(const EventInterface& events);
		
	private:
		GameState gameState;
		Level* level;
		Player* player;
		Platform* landedPlatform;
	};
}

#endif