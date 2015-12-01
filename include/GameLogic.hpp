#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <vector>
#include <iostream>
#include "Level.hpp"
#include "Player.hpp"
#include "Platform.hpp"
#include "FallingHazard.hpp"

#include "EventManager.hpp"
#include "GameOverEvent.hpp"
#include "GameStartEvent.hpp"
#include "GamePlayEvent.hpp"
#include "GamePauseEvent.hpp"
#include "GameRestartEvent.hpp"
#include "HitByFallingHazardEvent.hpp"


namespace lava
{
	class GameLogic
	{
	public:
		void update(float delta);
		GameLogic(Level* level, Player* player, eventManager *manager);
		void respond(const EventInterface& events);

		GameOverEvent gameOver;
		GameStartEvent gameStart;
		GamePlayEvent gamePlay;
		GamePauseEvent gamePause;
		GameRestartEvent gameRestart;
		HitByFallingHazardEvent hazardEvent;

		static const int A = 1100;
		static const int START_Y = 100000;
		
	private:
		Level* level;
		Player* player;
		eventManager *manager;
		Platform* landedPlatform;

		bool running;
	};
}

#endif
