#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <vector>
#include <iostream>
#include "Level.hpp"
#include "Player.hpp"
#include "ActorDestroyedEvent.hpp"
#include "EventManager.hpp"
#include "GameOverEvent.hpp"
#include "HitByFallingHazardEvent.hpp"
#include "Platform.hpp"
#include "FallingHazard.hpp"


namespace lava
{
	class GameLogic
	{
	public:
		void update(float delta);
		GameLogic(Level* level, Player* player, eventManager *manager);
		void respond(const EventInterface& events);

		GameOverEvent gameOver;
		HitByFallingHazardEvent hazardEvent;

		static const int A = 1100;
		static const int START_Y = 100000;
		
	private:
		Level* level;
		Player* player;
		eventManager *manager;
		Platform* landedPlatform;
	};
}

#endif
