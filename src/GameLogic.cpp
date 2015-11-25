#include "GameLogic.hpp"
#include <iostream>


namespace lava
{

	GameLogic::GameLogic(Level* level, Player* player, lava::eventManager *manager)
	{
		this->level = level;
		this->player = player;
		this->manager = manager;
		EventDelegate example(std::bind(&lava::GameLogic::respond, this, std::placeholders::_1), (int)this);
		this->manager->registerEvent(example, gameOver);
	}
	
	void GameLogic::update(float delta)
	{
		// update level
		for(int i=0; i < level->getPlatforms()->size(); i++)
		{
			Platform* platform = level->getPlatforms()->at(i);
			platform->update(delta);
		}
		level->update(player->getY(), delta);

		// update player
		player->update(delta);

		// check for landings
		for (int i = 0; i < level->getPlatforms()->size(); i++)
		{
			Platform* platform = level->getPlatforms()->at(i);

			// if they intersect and the player is high enough
			if (platform->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds()) 
				&& player->getY() + player->getSprite().getGlobalBounds().height < platform->getY() + platform->getSprite().getGlobalBounds().height)
			{
				if (player->isFalling()) player->land(platform->getY());
				landedPlatform = platform;
			}
		}

		// move player with platform
		if (player->landed)
		{
			player->stickToPlatform(delta, landedPlatform->getVelocityX());
		}

		// check for death
		if (player->getY() > level->getLavaY())
		{
			if (player->alive)
			{
				manager->queueEvent(&gameOver);
				player->die();
			}
		}
	}

	void GameLogic::respond(const EventInterface& events){
		if (events.getEventType() == ActorDestroyedEvent::eventId){
			std::cout << "HELLO WORLD\n";
		}
		else{
			std::cout << "GAME OVER \n";
		}
	}
}