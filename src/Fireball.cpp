#include "Fireball.hpp"
#include "GameLogic.hpp"

namespace lava
{
	Fireball::Fireball(double theta, int degree, int y, sf::Texture *boulderTexture) :
		vx(0),
		vy(0)
	{
		hazardSprite.setTexture(*boulderTexture);
		this->dy = (float)std::sin(theta) ;
		this->dx = (float)std::cos(theta);
		std::cout << (float)std::sin(theta) << std::endl;
		std::cout << (float)std::cos(theta) << std::endl;
		
		if (dy < 0 && dx > 0){
			hazardSprite.setPosition(0, y + 300);
			hazardSprite.setTextureRect(sf::IntRect(32, 32, 32, 32));
			std::cout << "Part one\n";
			//hazardSprite.rotate(100);
		}
		else if (dy > 0 && dx > 0){
			hazardSprite.setPosition(0, y - 300);
			hazardSprite.setTextureRect(sf::IntRect(64, 64, 32, 32));
			std::cout << "Part two\n";

		}
		else if (dy < 0 && dx < 0){
			hazardSprite.setPosition(750, y + 300);
			hazardSprite.setTextureRect(sf::IntRect(96, 32, 32, 32));
			std::cout << "Part three\n";
		}
		else{ //dy > 0 && dx < 0
			hazardSprite.setPosition(750, y - 300);
			hazardSprite.setTextureRect(sf::IntRect(64, 32, 32, 32));
			std::cout << "Part four\n";
		}

		this->theta = theta;

		float sizex = 1.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0 - 1.0)));

		hazardSprite.setScale(sizex, sizex);
	}

	void Fireball::update(float delta)
	{
		vy += dy * 300 *delta;
		vx += dx * 300 * delta;

		hazardSprite.move(vx*delta, vy * delta);
	}

	void Fireball::render(sf::RenderWindow* window)
	{
		window->draw(hazardSprite);
	}
}
