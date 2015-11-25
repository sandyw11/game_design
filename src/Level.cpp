#include "Level.hpp"
#include <cmath>

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
		lastX = 300;
		lastY = START_Y + 40;
		platforms.push_back(new Platform(lastX, lastY, 200,this->texture));

		chunkNum = 0;
		nextChunkY = START_Y - CHUNK_HEIGHT / 2;      // generate new chunk when player is halfway through old chunk
		generateChunk(this->texture);
	}

	Level::~Level() 
	{
		// remove all platforms
		platforms.empty();
	}

	void Level::generateChunk(sf::Texture *platformTexture)
	{
		int width, dx, dy;
		float theta, distance;
		chunkNum++;

		// generate up to chunk height
		while(lastY > START_Y - chunkNum * CHUNK_HEIGHT)
		{
			// get random angle between 20 and 160
			// TODO: not hardcoded
			theta = (float)(rand() % 140 + 20)/180 * 3.14159;
			distance = rand() % 150 + 100;
			width = rand() % 100 + 75;

			dx = distance * std::cos(theta);
			dy = distance * std::sin(theta);

			// double the dx -- more fun sequences
			lastX += 2*dx;
			lastY -= dy;

			// keep x within bounds
			if (lastX + width > 800 || lastX < 0) {
				lastX -= 3*dx;
			}

			platforms.push_back(new Platform(lastX, lastY, width,platformTexture));
			//std::cout << "Platform at " << lastX << ", " << lastY << "\n";
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
		std::vector<Platform*>::iterator it = platforms.begin();
		while (it != platforms.end())
		{
			Platform* platform = *it;
			if (platform->getY() > lavaY)
			{
				std::cout << "Deleting platform\n";
				it = platforms.erase(it);
			}
			else {
				++it;
			}
		}
	}
}