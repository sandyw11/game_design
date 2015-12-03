#include "Level.hpp"
#include "Random.hpp"
#include "GameLogic.hpp"
#include <cmath>
#include <iostream>

namespace lava
{
	Level::Level(int seed, sf::Texture *platformTexture, sf::Texture *hazardTexture, lava::eventManager *manager) :
	chunkNum(0),
	lavaY(GameLogic::START_Y + 400),
	lavaVy(START_LAVA_VY)
	{
		this->texture = platformTexture;
		this->hazardTexture = hazardTexture;
		this->manager = manager;

		// seed random number generator
		srand(seed);

		// starting platform
		lastX = START_X;
		lastY = GameLogic::START_Y + 40;
		platforms.push_back(new Platform(lastX, lastY, 200, this->texture));

		// first hazard created
		nextHazardTime = FIRST_HAZARD_TIME;
		nextFireballTime = FIRST_HAZARD_TIME;

		nextChunkY = GameLogic::START_Y - CHUNK_HEIGHT / 2;      // generate new chunk when player is halfway through old chunk
		generateChunk(this->texture);
	}

	Level::~Level()
	{
		// remove all platforms and powerups
		platforms.clear();
		powerups.clear();
		hazards.clear();
	}

	void Level::generateChunk(sf::Texture *platformTexture)
	{
		int width, dx, dy;
		float theta, distance;
		chunkNum++;

		// generate up to chunk height
		while(lastY > GameLogic::START_Y - chunkNum * CHUNK_HEIGHT)
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
			if (Equilikely(0, 35) == 1)
			{
				int powerupX = lastX + width/2 - Powerup::WIDTH/2;
				int powerupY = lastY - Powerup::HEIGHT;
				powerups.push_back(new Powerup(powerupX, powerupY, this->hazardTexture));
			}
		}

		//std::cout << "Chunk " << chunkNum << " generated\n";
	}

	void Level::update(float playerY, float delta)
	{
		// check for new chunk
		if (playerY < nextChunkY)
		{
			generateChunk(this->texture);
			deleteChunks();
			nextChunkY -= CHUNK_HEIGHT;
		}

		// check for new hazard
		if (nextHazardTime < 0)
		{
			int radius = Equilikely(13, 15);
			int x = Equilikely(0, 800);
			int y = playerY - Equilikely(HAZARD_MIN_OFFSET, HAZARD_MAX_OFFSET);
			hazards.push_back(new FallingHazard(x, y, radius, this->hazardTexture));

			// TODO: use Uniform()?
			nextHazardTime = Equilikely(MIN_HAZARD_TIME, MAX_HAZARD_TIME);
		}
		if (nextFireballTime < 0){
			int degrees = Equilikely(20, 80);
			float theta2 = (float)degrees / 180 * 3.14159;
			int side = Equilikely(0, 1);
			if (side == 0){
				theta2 = theta2 *-1;
				degrees = degrees * -1;
			}
			int y = playerY;
			fireballs.push_back(new Fireball(theta2, degrees, y, this->hazardTexture));

			// TODO: use Uniform()?
			nextFireballTime = Equilikely(MIN_HAZARD_TIME, MAX_HAZARD_TIME);
		}
		nextHazardTime -= delta;
		nextFireballTime -= delta*1.5;

		// accelerate and move lava
		lavaVy = (lavaVy < MAX_LAVA_VY) ? lavaVy + delta : MAX_LAVA_VY; // lava velocity increases 1/second
		if (lavaY - playerY > LAVA_CATCHUP_DISTANCE)  // if player is too far from lava, catch up
		{
			lavaY = lavaY - LAVA_CATCHUP_VY * delta;
		}
		else {
			lavaY = lavaY - lavaVy * delta;
		}
		
	}

	void Level::deleteChunks()
	{
		// TODO: more efficient deletion?

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

		// clean up unreachable hazards
		std::vector<FallingHazard*>::iterator hazardIt = hazards.begin();
		while (hazardIt != hazards.end())
		{
			FallingHazard* hazard = *hazardIt;
			if (hazard->getY() > lavaY)
			{
				hazardIt = hazards.erase(hazardIt);
			}
			else {
				++hazardIt;
			}
		}

		//clean up unreachable fireballs
		std::vector<Fireball*>::iterator fireballIt = fireballs.begin();
		while (fireballIt != fireballs.end())
		{
			Fireball* fire = *fireballIt;
			if (fire->getY() < playerY - 200){
				std::cout << "Special: " << fire->getY()<< std::endl;
			}
			if (fire->getY() > lavaY)
			{
				std::cout << "Deleting fireball\n";
				fireballIt = fireballs.erase(fireballIt);
			}
			else {
				++fireballIt;
			}
		}
	}

	void Level::reset()
	{
		// get rid of old level
		platforms.clear();
		powerups.clear();
		hazards.clear();
		fireballs.clear();

		// starting platform
		lastX = START_X;
		lastY = GameLogic::START_Y + 40;
		platforms.push_back(new Platform(lastX, lastY, 200, this->texture));

		// first hazard created
		nextHazardTime = FIRST_HAZARD_TIME;
		nextFireballTime = FIRST_HAZARD_TIME;

		chunkNum = 0;
		nextChunkY = GameLogic::START_Y - CHUNK_HEIGHT / 2;      // generate new chunk when player is halfway through old chunk
		generateChunk(this->texture);

		lavaY = GameLogic::START_Y + 400;
		lavaVy = START_LAVA_VY;
	}
}
