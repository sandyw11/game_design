#include <SFML/Graphics.hpp>
#include "GameView.hpp"

namespace lava
{
	GameView::GameView(sf::RenderWindow* window, std::vector<Actor*>* actors, Player* player)
	{
		this->window = window;
		this->actors = actors;
		this->player = player;
	}
    
    void GameView::setFont()
    {
        font.loadFromFile("font.ttf");
        /*if(!font.loadFromFile("font.ttf"))
        {
            return 0;
        }*/
    }
    
    void GameView::setStartMessage()
    {
        setFont();
        sf::Text startMessage("          START\n\n\npress Enter to start", font, 30);
        startMessage.setPosition(300, 200);
        startMessage.setColor(sf::Color::Red);
        window->draw(startMessage);
    }
    
    void GameView::setStart()
    {
        //window->clear(sf::Color::Black);
        setStartMessage();
    }
    
    void GameView::setPauseMessage()
    {
        setFont();
        sf::Text pauseMessage("          PAUSE\n\n\npress P to continue", font, 30);
        pauseMessage.setPosition(300, 200);
        pauseMessage.setColor(sf::Color::Red);
        window->draw(pauseMessage);
    }
    
    void GameView::setPause()
    {
        //window->clear(sf::Color::Black);
        setPauseMessage();
    }
    
    void GameView::setGameoverMessage()
    {
        setFont();
        sf::Text gameoverMessage("      GAME OVER\n\npress Enter to restart\n    press Esc to quit", font, 30);
        gameoverMessage.setPosition(300, 200);
        gameoverMessage.setColor(sf::Color::Red);
        window->draw(gameoverMessage);
    }
    
    void GameView::setGameover()
    {
        //window->clear(sf::Color::Black);
        setGameoverMessage();
    }

    void GameView::update(sf::Clock clock)
	{
        processInput(clock);
        
        window->clear(sf::Color::Black);
        if(isPlaying)
        {
            if(isWait)
            {
                setPause();
            }
            else
            {
                draw();
            }
        }
        else
        {
            if(isGameover)
            {
                setGameover();
            }
            else
            {
                setStart();
            }
        }
        window->display();
        
	}
	
    void GameView::processInput(sf::Clock clock)
	{
		sf::Event Event;
		while(window->pollEvent(Event))
		{
			// exit
            if((Event.type == sf::Event::Closed) || ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)))
				window->close();
			
<<<<<<< HEAD
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                if(!isPlaying)
                {
                    isPlaying = true;
                    isGameover = false;
                    clock.restart();
                }
            }
            
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::P))
            {
                isWait = !isWait;
            }
            
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::R))
            {
                if(isPlaying)
                {
                    isPlaying = false;
                }
            }
            
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Q))
            {
                if(!isGameover && isPlaying)
                {
                    isGameover = true;
                    isPlaying = false;
                }
            }
			
=======
>>>>>>> origin/master
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
<<<<<<< HEAD
		//window->clear(sf::Color::Black);
		sf::View view;
  		view.reset(sf::FloatRect(0, 0, 800, 600));
=======
		sf::View view;
>>>>>>> origin/master
		window->clear(sf::Color::Black);
		
		// draw actors
		for(int i=0; i < actors->size(); i++)
		{
			sf::Vector2f position(0, 0);
			Actor* actor = actors->at(i);
			actor->render(window);
			position.x = actor->getX() + 10 - (800 / 2);
			position.y = actor->getY() + 20 - (600 / 2);
			if (position.y < 0)
			{
				position.y = 0;
			}
			view.reset(sf::FloatRect(position.x, position.y, 800, 600));
		}
<<<<<<< HEAD
		sf::RectangleShape platform(sf::Vector2f(70, 20));
		platform.setFillColor(sf::Color::Green);
    	platform.setPosition(525, 300);
    	window->setView(view);
    	window->draw(platform);
        //window->display();
	}
}
}
=======
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
>>>>>>> origin/master
