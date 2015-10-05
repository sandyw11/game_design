#include "GameLogic.hpp"

namespace lava
{
	GameLogic::GameLogic(std::vector<Actor*>* actors)
	{
		this->actors = actors;
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