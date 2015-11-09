#include "Level.hpp"

namespace lava
{
	Level::Level(int seed):
	chunkNum(0),
	lavaY(START_Y+400),
	lavaVy(START_LAVA_VY)
	{
		srand(seed);
		chunkNum = 0;
		nextChunkY = START_Y - CHUNKHEIGHT/2;
		generateChunk();

		// starting platform
		platforms.push_back(new Platform(525, START_Y + 40, 200));
	}

	Level::~Level() 
	{
		// remove all platforms
		platforms.empty();
	}

	void Level::generateChunk()
	{
		// generate up to chunk height
		for (int h = 0; h <= CHUNKHEIGHT; h += rand() % 100 + 100)
		{
				int x = rand() % WIDTH;
				int width = rand() % 100 + 75;
				platforms.push_back(new Platform(x, START_Y - h - chunkNum * CHUNKHEIGHT, width));
				std::cout << "Platform at " << x << ", " << h << "\n";
		}
		chunkNum++;
		std::cout << "Chunk " << chunkNum << "\n";
	}

	void Level::update(float playerY, float delta)
	{
		if (playerY < nextChunkY)
		{
			generateChunk();
			deleteChunks();
			nextChunkY -= CHUNKHEIGHT;
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