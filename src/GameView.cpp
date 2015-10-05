#include "GameView.hpp"

namespace lava
{
	GameView::GameView(sf::RenderWindow* window, std::vector<Actor*>* actors)
	{
		this->window = window;
		this->actors = actors;
	}
	
	void GameView::update(float delta)
	{
		
	}
}