#include "Level.hpp"
#include "Random.hpp"
#include <cmath>
#include <iostream>

namespace lava
{
	Level::Level(int seed, sf::Texture *platformTexture, lava::eventManager *manager) :
	chunkNum(0),
	lavaY(START_Y+400),
	lavaVy(START_LAVA_VY)
	{
		this->texture = platformTexture;
		this->manager = manager;

		// seed random number generator
		srand(seed);

		// starting platform
		lastX = START_X;
		lastY = START_Y + 40;
		platforms.push_back(new Platform(lastX, lastY, 200,this->texture));

		chunkNum = 0;
		nextChunkY = START_Y - CHUNK_HEIGHT / 2;      // generate new chunk when player is halfway through old chunk
		generateChunk(this->texture);
	}

	Level::~Level()
	{
		// remove all platforms and powerups
		platforms.empty();
		powerups.empty();
	}

	void Level::generateChunk(sf::Texture *platformTexture)
	{
		int width, dx, dy;
		float theta, distance;
		chunkNum++;

		// generate up to chunk height
		while(lastY > START_Y - chunkNum * CHUNK_HEIGHT)
		{
			// random angle between 20 and 160
			theta = (float) Equilikely(MIN_THETA, MAX_THETA)/180 * 3.14159;
			distance = Equilikely(MIN_DIST, MAX_DIST);
			width = Equilikely(MIN_WIDTH, MAX_WIDTH);

			// get x/y distance from last platform
			dx = distance * std::cos(theta);
			dy = distance * std::sin(theta);

			// double the dx -- more fun sequences
			lastX += 2*dx;
			lastY -= dy;

			// keep x within bounds
			if (lastX + width > 800 || lastX < 0) {
				lastX -= 3*dx;
			}

			platforms.push_back(new Platform(lastX, lastY, width, platformTexture));
			std::cout << "Platform at " << lastX << ", " << lastY << "\n";

			// random chance of a powerup
			// TODO: stick to platforms that move
			if (Equilikely(0, 20) == 1)
			{
				int powerupX = lastX + width/2 - Powerup::WIDTH/2;
				int powerupY = lastY - Powerup::HEIGHT;
				powerups.push_back(new Powerup(powerupX, powerupY));
			}
		}

		//std::cout << "Chunk " << chunkNum << " generated\n";
	}

	void Level::update(float playerY, float delta)
	{
		if (playerY < nextChunkY)
		{
			generateChunk(this->texture);
			deleteChunks();
			nextChunkY -= CHUNK_HEIGHT;
		}

		lavaVy = (lavaVy < MAX_LAVA_VY) ? lavaVy + 1 * delta : MAX_LAVA_VY;
		lavaY = lavaY - lavaVy * delta;
	}

	void Level::deleteChunks()
	{
		// delete unreachable chunks
		std::vector<Platform*>::iterator platformIt = platforms.begin();
		while (platformIt != platforms.end())
		{
			Platform* platform = *platformIt;
			if (platform->getY() > lavaY)
			{
				std::cout << "Deleting platform\n";
				platformIt = platforms.erase(platformIt);
			}
			else {
				++platformIt;
			}
		}

		// clean up unreachable powerups
		std::vector<Powerup*>::iterator powerupIt = powerups.begin();
		while (powerupIt != powerups.end())
		{
			Powerup* powerup = *powerupIt;
			if (powerup->getY() > lavaY)
			{
				std::cout << "Deleting powerup\n";
				powerupIt = powerups.erase(powerupIt);
			}
			else {
				++powerupIt;
			}
		}
	}
	
	void Level::resetLava()
	{
		lavaY = START_Y+400;
		lavaVy = START_LAVA_VY;
	}
}
