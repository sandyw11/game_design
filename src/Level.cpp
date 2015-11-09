#include "Level.hpp"

namespace lava
{
	Level::Level(int seed):
	chunkNum(0),
	lavaY(START_Y+500),
	lavaVy(20)
	{
		srand(seed);
		chunkNum = 0;
		nextChunkY = START_Y - CHUNKHEIGHT/2;
		generateChunk();

		// starting platform
		platforms.push_back(new Platform(525, START_Y + 30, 200));
	}

	Level::~Level() {}

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

	void Level::update(float playerY)
	{
		if (playerY < nextChunkY)
		{
			generateChunk();
			nextChunkY -= CHUNKHEIGHT;
		}
	}

	void Level::deleteChunks()
	{
		// delete unreachable chunks
	}
}