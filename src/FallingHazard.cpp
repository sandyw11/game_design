#include "FallingHazard.hpp"
#include "GameLogic.hpp"

namespace lava
{
	FallingHazard::FallingHazard(int x, int y, int radius, sf::Texture *boulderTexture):
	vx(0),
	vy(0)
	{
		hazardSprite.setTexture(*boulderTexture);
		hazardSprite.setPosition(x, y);
		hazardSprite.setTextureRect(sf::IntRect(0, 64, 32, 32));

		float sizex = 1.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0 - 1.0)));

		hazardSprite.setScale(sizex, sizex);
	}

	void FallingHazard::update(float delta)
	{
		// acceleration from gravity
		vy += GameLogic::A * delta;
		hazardSprite.move(vx*delta, vy * delta);
	}

	void FallingHazard::render(sf::RenderWindow* window)
	{
		window->draw(hazardSprite);
	}
}
