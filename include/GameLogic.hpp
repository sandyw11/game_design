#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <vector>
#include <iostream>
#include "Level.hpp"
#include "Player.hpp"
#include "ActorDestroyedEvent.hpp"
#include "EventManager.hpp"
#include "GameOverEvent.hpp"
#include "Platform.hpp"
#include "FallingHazard.hpp"


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
		GameLogic(Level* level, Player* player,lava::eventManager *manager);
		void respond(const EventInterface& events);
		GameOverEvent gameOver;

		static const int A = 1100;
		
	private:
		GameState gameState;
		Level* level;
		Player* player;
		lava::eventManager *manager;
		Platform* landedPlatform;
	};
}

#endif