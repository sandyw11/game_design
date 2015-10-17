#include "GameLogic.hpp"

namespace lava
{
	GameLogic::GameLogic(std::vector<Actor*>* actors, Player* player)
	{
		this->actors = actors;
		this->player = player;
	}
	
	void GameLogic::update(float delta)
	{
		// update actors
		for(int i=0; i < actors->size(); i++)
		{
			Actor* actor = actors->at(i);
			actor->update(delta);
		}
	}
}