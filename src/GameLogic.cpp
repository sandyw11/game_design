#include "GameLogic.hpp"

namespace lava
{
	GameLogic::GameLogic(Level* level, Player* player)
	{
		this->level = level;
		this->player = player;
	}
	
	void GameLogic::update(float delta)
	{
		// update level
		for(int i=0; i < level->getPlatforms()->size(); i++)
		{
			Platform* platform = level->getPlatforms()->at(i);
			platform->update(delta);
		}
		level->update(player->getY());

		// update player
		player->update(delta);

		// check for landings
		for (int i = 0; i < level->getPlatforms()->size(); i++)
		{
			Platform* platform = level->getPlatforms()->at(i);

			// if they intersect and the player is high enough
			if (platform->getRect().getGlobalBounds().intersects(player->getRect().getGlobalBounds()) 
				&& player->getY() + player->getRect().getSize().y < platform->getY() + platform->getRect().getSize().y)
			{
				if (player->isFalling()) player->land(platform->getY());
			}
		}
	}
}