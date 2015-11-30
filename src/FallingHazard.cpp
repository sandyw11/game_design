#include "FallingHazard.hpp"
#include "GameLogic.hpp"

namespace lava
{
	FallingHazard::FallingHazard(int x, int y, int radius):
	circ(sf::CircleShape(radius)),
	vx(0),
	vy(0)
	{
		circ.setPosition(x, y);

		// TODO: plz sprite or better graphics
		circ.setFillColor(sf::Color::White);
	}

	void FallingHazard::update(float delta)
	{
		// acceleration from gravity
		vy += GameLogic::A * delta;
		circ.move(vx*delta, vy * delta);
	}

	void FallingHazard::render(sf::RenderWindow* window)
	{
		window->draw(circ);
	}
}