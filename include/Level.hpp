#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <cstdlib>
#include <iostream>
#include "Platform.hpp"

namespace lava
{
	class Level
	{
	private:
		static const int WIDTH = 800;
		static const int CHUNKHEIGHT = 1200;
		static const int START_Y = 50000;
		int chunkNum;

		std::vector<Platform*> platforms;
		float playerY;
		float nextChunkY;
		float lavaY;
		float lavaVy;

		void deleteChunks();
		void generateChunk();

	public:
		Level(int seed);
		~Level();

		std::vector<Platform*>* getPlatforms() { return &platforms; };
		int getLavaY() { return lavaY; }
		void update(float playerY, float delta);
	};
}

#endif