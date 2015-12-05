#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include "Platform.hpp"
#include "Powerup.hpp"
#include "FallingHazard.hpp"
#include "GameOverEvent.hpp"
#include "EventManager.hpp"
#include "Fireball.hpp"

namespace lava
{
	class Level
	{
	private:
		static const int WIDTH = 800;
		static const int CHUNK_HEIGHT = 1200;
		static const int START_X = 300;
		static const int START_LAVA_VY = 60;
		static const int MAX_LAVA_VY = 170;
		static const int LAVA_CATCHUP_VY = 200;
		static const int LAVA_CATCHUP_DISTANCE = 1000;

		static const int MIN_THETA = 20;
		static const int MAX_THETA = 160;
		static const int MIN_DIST = 100;
		static const int MAX_DIST = 250;
		static const int MIN_WIDTH = 75;
		static const int MAX_WIDTH = 175;

		static const int FIRST_HAZARD_TIME = 30;
		static const int MIN_HAZARD_TIME = 2;
		static const int MAX_HAZARD_TIME = 5;

		static const int HAZARD_MIN_OFFSET = 325;
		static const int HAZARD_MAX_OFFSET = 400;
		static const int HAZARD_RADIUS = 16;

		static const int FIRST_FIREBALL_TIME = 60;
		static const int MIN_FIREBALL_TIME = 5;
		static const int MAX_FIREBALL_TIME = 8;


		int chunkNum;
		sf::Texture *texture;
		sf::Texture *hazardTexture;

		std::vector<Platform*> platforms;
		std::vector<Powerup*> powerups;
		std::vector<FallingHazard*> hazards;
		std::vector<Fireball*> fireballs;
		lava::eventManager *manager;

		float playerY;
		float nextChunkY;
		float nextHazardTime;
		float nextFireballTime;
		float lavaY;
		float lavaVy;

		// remember X, Y positions of last platform
		float lastX;
		float lastY;

		void deleteChunks();
		void generateChunk(sf::Texture *platformTexture);

	public:
		Level(int seed, sf::Texture* platformTexture, sf::Texture *hazardTexture, lava::eventManager *manager);
		~Level();

		std::vector<Platform*>* getPlatforms() { return &platforms; }
		std::vector<Powerup*>* getPowerups() { return &powerups; }
		std::vector<FallingHazard*>* getFallingHazards() { return &hazards; }
		std::vector<Fireball*>* getFireballs() { return &fireballs; }

		int getLavaY() { return lavaY; }
		void reset();
		void update(float playerY, float delta);
	};
}

#endif
