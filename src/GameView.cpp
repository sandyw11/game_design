#include "GameView.hpp"

namespace lava
{
	GameView::GameView(sf::RenderWindow* window, std::vector<Actor*>* actors, Player* player)
	{
		this->window = window;
		this->actors = actors;
		this->player = player;
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
			
			// key press events
			if(Event.type == sf::Event::KeyPressed)
			{
				switch(Event.key.code)
				{
					case sf::Keyboard::Space:
						player->charging = true;
						break;
					case sf::Keyboard::D:
						player->moveLeft = true;
						break;
					case sf::Keyboard::A:
						player->moveRight = true;
						break;
				}
			}
			
			// key release events
			if(Event.type == sf::Event::KeyReleased)
			{
				switch(Event.key.code)
				{
					case sf::Keyboard::Space:
						player->charging = false;
						player->jump();
						break;
					case sf::Keyboard::D:
						player->moveLeft = false;
						break;
					case sf::Keyboard::A:
						player->moveRight = false;
						break;
				}
			}
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