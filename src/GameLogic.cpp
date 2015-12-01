#include "GameLogic.hpp"
#include <iostream>


namespace lava
{

	GameLogic::GameLogic(Level* level, Player* player, lava::eventManager *manager)
	{
		this->level = level;
		this->player = player;
		this->manager = manager;

		EventDelegate example(std::bind(&GameLogic::respond, this, std::placeholders::_1), (int)this);
		this->manager->registerEvent(example, gameOver);
	}
	
	void GameLogic::update(float delta)
	{
		// update platforms
		for (auto &platform : *level->getPlatforms())
		{
			platform->update(delta);

			// check for landings
			// landing = they intersect and the player is high enough
			if (platform->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())
				&& player->getY() + player->getSprite().getGlobalBounds().height < platform->getY() + platform->getSprite().getGlobalBounds().height)
			{
				if (player->isFalling()) player->land(platform->getY());
				landedPlatform = platform;
				platform->startFall();
			}
		}

		// update level
		level->update(player->getY(), delta);

		// update player
		player->update(delta);

		// check for powerup collision
		std::vector<Powerup*>::iterator powerupIt = level->getPowerups()->begin();
		while (powerupIt != level->getPowerups()->end())
		{
			Powerup* powerup = *powerupIt;
			if (powerup->getRect().getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
			{
				// TODO: initiate powerup effect
				std::cout << "got powerup " << powerup->getType() << "\n";
				powerupIt = level->getPowerups()->erase(powerupIt);
			}
			else {
				++powerupIt;
			}
		}

		// update falling hazards
		std::vector<FallingHazard*>::iterator hazardIt = level->getFallingHazards()->begin();
		while (hazardIt != level->getFallingHazards()->end())
		{
			FallingHazard* hazard = *hazardIt;
			hazard->update(delta);

			// check collision
			if (hazard->getCircle().getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
			{
				player->hitByRock(hazard->getVy());
				hazardIt = level->getFallingHazards()->erase(hazardIt);
				manager->queueEvent(&hazardEvent);
			} else {
				++hazardIt;
			}
		}

		// move player with platform
		if (player->landed)
		{
			player->stickToPlatform(delta, landedPlatform->getVelocityX(), landedPlatform->getVelocityY());
		}

		// check for death by lava
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

	}
}
