#include "GameLogic.hpp"
#include <iostream>


namespace lava
{

	GameLogic::GameLogic(Level* level, Player* player, lava::eventManager *manager):
	running(false)
	{
		this->level = level;
		this->player = player;
		this->manager = manager;

		EventDelegate delegate(std::bind(&GameLogic::respond, this, std::placeholders::_1), (int)this);

		// respond to state changes
		this->manager->registerEvent(delegate, gameOver);
		this->manager->registerEvent(delegate, gameStart);
		this->manager->registerEvent(delegate, gamePlay);
		this->manager->registerEvent(delegate, gamePause);
		this->manager->registerEvent(delegate, gameRestart);
	}

	void GameLogic::update(float delta)
	{
		if(running)
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

				if (powerup->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
				{
					std::cout << "got powerup " << powerup->getType() << "\n";
					player->applyPowerup(powerup->getType());
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
					hazardIt = level->getFallingHazards()->erase(hazardIt);
					if (!player->immune){
						player->hitByRock(hazard->getVy());
						manager->queueEvent(&hazardEvent);
					}
				} else {
					++hazardIt;
				}
				
			}

			std::vector<Fireball*>::iterator fireballIt = level->getFireballs()->begin();
			while (fireballIt != level->getFireballs()->end())
			{
				Fireball* fireball= *fireballIt;
				fireball->update(delta);

				// check collision
				if (fireball->getCircle().getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
				{
					fireballIt = level->getFireballs()->erase(fireballIt);
					if (!player->immune){
						if (player->life != 0){
							player->hitByFire();
							manager->queueEvent(&hazardEvent);
						}
						else{
							player->die();
							manager->queueEvent(&gameOver);
						}
					}
				}
				else {
					++fireballIt;
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
	}

	void GameLogic::respond(const EventInterface& events){
		// events that stop gameplay
		if (events.getEventType() == GameOverEvent::eventId
	    	|| events.getEventType() == GamePauseEvent::eventId)
		{
			running = false;
		}
		// events that resume/start gameplay
		else if (events.getEventType() == GamePlayEvent::eventId)
		{
			running = true;
		}
	}
}
