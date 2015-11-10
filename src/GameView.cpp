#include <SFML/Graphics.hpp>
#include "GameView.hpp"

namespace lava
{
	GameView::GameView(sf::RenderWindow* window, std::vector<Actor*>* actors, Player* player):
	isWait(false),
	isPlaying(false),
	isGameover(false)
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
<<<<<<< HEAD
        
=======

		sf::View view;
		view.reset(sf::FloatRect(0, 0, 800, 600));

>>>>>>> master
        window->clear(sf::Color::Black);
        if(isPlaying)
        {
            if(isWait)
            {
<<<<<<< HEAD
=======
				window->setView(view);
>>>>>>> master
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
<<<<<<< HEAD
=======
				window->setView(view);
>>>>>>> master
                setGameover();
            }
            else
            {
<<<<<<< HEAD
=======
				window->setView(view);
>>>>>>> master
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
            
            if(Event.type == sf::Event::KeyPressed)
            {
                switch(Event.key.code)
                {
                    case sf::Keyboard::Space:
                        player->charging = true;
                        break;
                }
            }
            
            if(Event.type == sf::Event::KeyReleased)
            {
                switch(Event.key.code)
                {
                    case sf::Keyboard::Space:
                        player->charging = false;
                        player->jump();
                        break;
                }
            }
=======
			
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
>>>>>>> master
		}
	}
	
	void GameView::draw()
	{
<<<<<<< HEAD
		//window->clear(sf::Color::Black);
=======
		sf::View view;
  		view.reset(sf::FloatRect(0, 0, 800, 600));
		window->clear(sf::Color::Black);
>>>>>>> master
		
		// draw actors
		for(int i=0; i < actors->size(); i++)
		{
			Actor* actor = actors->at(i);
			actor->render(window);
		}
<<<<<<< HEAD
		
		//window->display();
	}
    
    
    /*void GameView::drawBackground()
    {
        window->clear(sf::Color::Black);
        window->draw(start);
        // draw background
        switch(gamestate)
        {
            case START:
                setStart;
                break;
            case PLAY:
                setPlay;
                break;
            case PAUSE:
                setPause;
                break;
            case GAMEOVER:
                setGameover
                break;
        }
    }*/
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
	}
}
>>>>>>> master
