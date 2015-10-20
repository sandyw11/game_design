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
		sf::View view;
		window->clear(sf::Color::Black);
		
		// draw actors
		for(int i=0; i < actors->size(); i++)
		{
			Actor* actor = actors->at(i);
			actor->render(window);
		}
		sf::Vector2f position(0, 0);
		position.x = player->getX() + 10 - (800 / 2);
		position.y = player->getY() + 20 - (600 / 2);
		if (position.y < 0)
		{
			position.y = 0;
		}
		view.reset(sf::FloatRect(position.x, position.y, 800, 600));

    	window->setView(view);
		window->display();
	}
}
