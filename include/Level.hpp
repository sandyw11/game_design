#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <cstdlib>
#include <iostream>
#include "Platform.hpp"
#include "Powerup.hpp"

namespace lava
{
	class Level
	{
	private:
		static const int WIDTH = 800;
		static const int CHUNK_HEIGHT = 1200;
		static const int START_Y = 50000;
		static const int START_LAVA_VY = 60;
		static const int MAX_LAVA_VY = 150;
		int chunkNum;

		std::vector<Platform*> platforms;
		float playerY;
		float nextChunkY;
		float lavaY;
		float lavaVy;

		// remember X, Y positions of last platform
		float lastX;
		float lastY;

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