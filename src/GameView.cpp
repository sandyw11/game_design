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
		processInput();
		draw();
	}
	
	void GameView::processInput() 
	{
		sf::Event Event;
		while(window->pollEvent(Event))
		{
			// exit
			if(Event.type == sf::Event::Closed)
			window->close();
		}
	}
	
	void GameView::draw()
	{
		window->clear(sf::Color::Black);
		
		// draw actors
		for(int i=0; i < actors->size(); i++)
		{
			Actor* actor = actors->at(i);
			actor->render(window);
		}
		
		window->display();
	}
}