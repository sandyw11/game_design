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
		}
	}
	
	void GameView::draw()
	{
		//window->clear(sf::Color::Black);
		
		// draw actors
		for(int i=0; i < actors->size(); i++)
		{
			Actor* actor = actors->at(i);
			actor->render(window);
		}
		
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