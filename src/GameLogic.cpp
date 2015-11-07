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

		// check for landings
		for (int i = 0; i < actors->size(); i++)
		{
			Actor* actor = actors->at(i);
			if (player != actor)
			{
				// if they intersect and the player is high enough
				if (actor->getRect().getGlobalBounds().intersects(player->getRect().getGlobalBounds()) 
					&& player->getY() + player->getRect().getSize().y < actor->getY() + actor->getRect().getSize().y)
				{
					if (player->isFalling()) player->land(actor->getY());
				}
			}
		}
	}
	void GameLogic::respond(const EventInterface& events){
		if (events.getEventType() == ActorDestroyedEvent::eventId){
			std::cout << "HELLO WORLD\n";
		}
		else{
			std::cout << "NO EVENT \n";
		}
	}
}