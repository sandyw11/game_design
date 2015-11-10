#include <SFML/Graphics.hpp>
#include "GameView.hpp"
#include "GameGUI.hpp"

namespace lava
{
    GameView::GameView(sf::RenderWindow* window, std::vector<Actor*>* actors, Player* player)
	{
		this->window = window;
		this->actors = actors;
		this->player = player;
    }
    
    GameView::~GameView()
    {

    }

    GameGUI gameGUI(800, 600);
    
    void GameView::setStart()
    {
        gameGUI.draw(window);
    }
    
    void GameView::setInstructionMessage()
    {
        sf::Texture texture;
        texture.loadFromFile("graph/instruction.jpg");
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, window->getSize().x, window->getSize().y));
        window->draw(sprite);
    }
    
    void GameView::setInstruction()
    {
        setInstructionMessage();
    }
    
    void GameView::setPauseMessage()
    {
        sf::Text pauseMessage("          PAUSE\n\n\npress [P] to continue", gameGUI.font, 30);
        pauseMessage.setPosition(300, 200);
        pauseMessage.setColor(sf::Color::Red);
        window->draw(pauseMessage);
    }
    
    void GameView::setPause()
    {
        setPauseMessage();
    }
    
    void GameView::setGameoverMessage()
    {
        sf::Text gameoverMessage("      GAME OVER\n\npress [Enter] to restart\n    press Esc to quit", gameGUI.font, 30);
        gameoverMessage.setPosition(300, 200);
        gameoverMessage.setColor(sf::Color::Red);
        window->draw(gameoverMessage);
    }
    
    void GameView::setGameover()
    {
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
                if(isWait)
                {
                    setInstruction();
                }
                else
                {
                    setStart();
                }
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
            {
				window->close();
            }
			
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
                if(!isPlaying)
                {
                    gameGUI.MoveUp();
                }
            }
            
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            {
                if(!isPlaying)
                {
                    gameGUI.MoveDown();
                }
            }
            
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {
                if(!isPlaying)
                {
                    switch(gameGUI.GetPressedItem())
                    {
                        case 0:
                            isPlaying = true;
                            isGameover = false;
                            clock.restart();
                            break;
                            
                        case 1:
                            isWait = true;
                            break;
                            
                        case 2:
                            window->close();
                            break;
                    }
                }
            }
            
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::M))
            {
                if(!isPlaying)
                {
                    isWait = false;
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
		// draw actors
		for(int i=0; i < actors->size(); i++)
		{
			Actor* actor = actors->at(i);
			actor->render(window);
		}
	}s
}
