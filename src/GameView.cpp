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
<<<<<<< HEAD

		sf::View view;
		view.reset(sf::FloatRect(0, 0, 800, 600));

=======
        
>>>>>>> origin/game-state
        window->clear(sf::Color::Black);
        if(isPlaying)
        {
            if(isWait)
            {
<<<<<<< HEAD
				window->setView(view);

=======
>>>>>>> origin/game-state
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
				window->setView(view);

=======
>>>>>>> origin/game-state
                setGameover();
            }
            else
            {
<<<<<<< HEAD
				window->setView(view);

                setStart();
=======
                if(isWait)
                {
                    setInstruction();
                }
                else
                {
                    setStart();
                }
>>>>>>> origin/game-state
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
<<<<<<< HEAD
=======
            }
>>>>>>> origin/game-state
			
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
=======
>>>>>>> origin/game-state
		}
	}
	
	void GameView::draw()
	{
<<<<<<< HEAD

		sf::View view;
  		view.reset(sf::FloatRect(0, 0, 800, 600));
		window->clear(sf::Color::Black);
		
=======
>>>>>>> origin/game-state
		// draw actors
		for(int i=0; i < actors->size(); i++)
		{
			Actor* actor = actors->at(i);
			actor->render(window);
		}
<<<<<<< HEAD

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
=======
	}s
>>>>>>> origin/game-state
}
