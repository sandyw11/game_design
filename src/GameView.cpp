#include "GameView.hpp"
#include <string>

namespace lava
{
	GameView::GameView(sf::RenderWindow* window, Level* level, Player* player, sf::View view, sf::Texture *lavaTexture, sf::Texture *backgroundTexture, sf::Texture *life, lava::eventManager *manager, LocalScoreboard *localscores) :
	isWait(false),
	isPlaying(false),
	isGameover(false),
	isInstruct(false),
	gameGUI(new GameGUI(800, 600))
	{
		this->window = window;
		this->level = level;
		this->player = player;
        this->view = view;
		this->manager = manager;
		this->localscores = localscores;
		background.setTexture(*backgroundTexture);

		lifeSprite.setTexture(*life);

		lavaSprite.setTexture(*lavaTexture);
		lavaSprite.setTextureRect(sf::IntRect(0, 0, 2400, 2000));
		lavaSprite.setScale(1, 1.5f);

		font.loadFromFile("pixel_font.ttf");
		text.setFont(font);
		text.setColor(sf::Color::White);
		text.setString("0");
		text.setCharacterSize(50);
		text.setPosition(sf::Vector2f(300, 200));

		EventDelegate example(std::bind(&lava::GameView::respond, this, std::placeholders::_1), (int)this);

		earthquakeBuffer.loadFromFile("earthquake.wav");
		earthquakeSound.setBuffer(earthquakeBuffer);
		earthquakeSound.setLoop(true);
		earthquakeSound.setBuffer(earthquakeBuffer);

		hazardBuffer.loadFromFile("hazard.flac");
		hazardSound.setBuffer(hazardBuffer);

       		jumpBuffer.loadFromFile("jump.wav");
		jumpSound.setBuffer(jumpBuffer);

      		gameOverBuffer.loadFromFile("Game_Over.wav");
		gameOverSound.setBuffer(gameOverBuffer);

		gamePlayMusic.openFromFile("Game_Play_Music.ogg");
		gamePlayMusic.setLoop(true);

		startScreenMusic.openFromFile("Start_Screen.ogg");
		startScreenMusic.setLoop(true);

		pauseScreenMusic.openFromFile("Pause_Screen.ogg");
		pauseScreenMusic.setLoop(true);

		this->manager->registerEvent(example, gameOver);
		this->manager->registerEvent(example, gameStart);
		this->manager->registerEvent(example, gamePlay);
		this->manager->registerEvent(example, gamePause);
		this->manager->registerEvent(example, gameRestart);

		this->manager->registerEvent(example, earthquake);
		this->manager->registerEvent(example, playingMusic);
		this->manager->registerEvent(example, jump);
		this->manager->registerEvent(example, loser);
		this->manager->registerEvent(example, startMusic);
		this->manager->registerEvent(example, pauseMusic);
		this->manager->registerEvent(example, hazardEvent);
    	}

	GameView::~GameView()
	{
		//delete gameGUI;
	}

    void GameView::setStart()
    {
        gameGUI->draw(window);
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

    void GameView::setPauseMessage()
    {
        sf::Text pauseMessage("          PAUSE\n\n\npress [P] to continue", font, 30);
        pauseMessage.setPosition(300, 200);
        pauseMessage.setColor(sf::Color::Red);
        window->draw(pauseMessage);
    }

    void GameView::setGameoverMessage()
    {
		sf::Text gameOverMessage(" ",font);
		sf::Text title(" ", font);
		title.setString("Your score: " + std::to_string(player->score) + "\n");
		title.setCharacterSize(100);
		title.setPosition(140, 0);
		title.setColor(sf::Color::Yellow);
		gameOverMessage.setString(highscorelist);

		if (highscorelist.empty()){
			localscores->load("Highscores.txt");
			for (int i = 0; i< localscores->size(); ++i) {
				LocalScoreboard::Entry e = localscores->getEntry(i);
				std::string rank = static_cast<std::ostringstream*>(&(std::ostringstream() << i + 1))->str();
				std::string scores = static_cast<std::ostringstream*>(&(std::ostringstream() << e.score))->str();
				std::cout << e.name << "\t-\t" << e.score << std::endl;
				highscorelist += "Rank " + rank + "  Name: " + e.name + "  High Score: " + scores + "\n";
			}
			localscores->save("Highscores.txt");
		}
			//
			//highscorelist.clear();
		gameOverMessage.setString(highscorelist);
		gameOverMessage.setCharacterSize(50);
		gameOverMessage.setPosition(200, 100);

		sf::Text gameoverMessage("     GAME OVER\npress [R] to restart\n  press Esc to quit", font, 30);
		gameoverMessage.setPosition(320, 450);
		gameoverMessage.setColor(sf::Color::Red);

		window->draw(title);
		window->draw(gameOverMessage);
		window->draw(gameoverMessage);
    }

    void GameView::drawChargeBar()
    {
	float chargedvy = std::sqrt(player->getCharge()) * 720;
	if (chargedvy > 1000)
	{
		chargedvy = 1000;
	}
	float chargenum = chargedvy / 1000 * 100;


        // draw chargebar frame
        sf::RectangleShape chargeBarFrame;
        chargeBarFrame.setPosition(650, player->getY() + 20 - (250) + 20);
        chargeBarFrame.setSize(sf::Vector2f(100, 20));
        chargeBarFrame.setFillColor(sf::Color::Black);
        chargeBarFrame.setOutlineColor(sf::Color::White);
        chargeBarFrame.setOutlineThickness(3);

        // draw charged part
        sf::RectangleShape chargedBar;
        chargedBar.setPosition(650, player->getY() + 20 - (250) + 20);
        if(chargenum > 100)
        {
            chargenum = 100;
        }
        chargedBar.setSize(sf::Vector2f(chargenum, 20));
        chargedBar.setFillColor(sf::Color::White);
        chargedBar.setOutlineColor(sf::Color::White);
        chargedBar.setOutlineThickness(0);

        window->draw(chargeBarFrame);
        window->draw(chargedBar);
    }

    void GameView::update(sf::Clock clock)
    {
        processInput(clock);
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 800, 600));

        window->clear(sf::Color::Black);
        if(isPlaying)
        {
            if (startScreenMusic.getStatus() != 0)
            {
                startScreenMusic.stop();
            }
            if (gameOverSound.getStatus() != 0)
            {
                gameOverSound.stop();
            }
            if(isWait)
            {
		window->setView(view);
		earthquakeSound.stop();
                setPauseMessage();
            }
            else
            {
                draw();
            }
        }
        else
        {
            window->setView(view);
            if(isGameover)
            {
				setGameoverMessage();
            }
            else
            {
                //window->setView(view);
                //setStart();
                if (startScreenMusic.getStatus() == 0)
                {
                    manager->queueEvent(&startMusic);
                }

                if(isInstruct)
                {
                    setInstructionMessage();
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
                    			gameGUI->MoveUp();
                		 }
            		}

            		if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
            		{
                		 if(!isPlaying)
                		 {
                    			gameGUI->MoveDown();
                		 }
            		}

                        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::M))
            		{
               			 if(!isPlaying)
                		 {
                             isInstruct = false;
               			 }
            		}

            		if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            		{
               			if(!isPlaying)
               			{
					switch(gameGUI->GetPressedItem())
		    			{
	       		 		case 0:
				                startScreenMusic.stop();
				                manager->queueEvent(&gamePlay);
				                manager->queueEvent(&playingMusic);

				                clock.restart();
				                player->alive = true;
				                player->resetPosition();
				                level->reset();
				                lavaSprite.setPosition(sf::Vector2f(-600, level->getLavaY()));
				                player->score = 0;
								player->life = 2;
								player->extra = 0;
				                break;
				        case 1:
				                isInstruct = true;
				                break;
				        case 2:
				                window->close();
				                break;
		    			}
                        	}
            		}

		    if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::R))
           	    {
                    	if(isGameover)
                    	{
                        	gameOverSound.stop();
                        	manager->queueEvent(&startMusic);
                        	manager->queueEvent(&gameRestart);
                    	}
                    }

		    if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::P))
		    {
		        if(isPlaying)
		        {
		            isWait = !isWait;
		            if (isWait == true)
		            {
		                gamePlayMusic.stop();
		                jumpSound.stop();
		                manager->queueEvent(&pauseMusic);
		                manager->queueEvent(&gamePause);
		            }
		            else
		            {
		                pauseScreenMusic.stop();
		                manager->queueEvent(&playingMusic);
		                manager->queueEvent(&gamePlay);
		            }
		        }
		    }

		    if(!isWait)
		    {
		        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Q))
		        {
				if(isPlaying)
				{
					gamePlayMusic.stop();
					manager->queueEvent(&loser);
					manager->queueEvent(&gameOver);
				}
			}


		        // key press events
		        if(Event.type == sf::Event::KeyPressed)
		        {

		            	switch(Event.key.code)
		            	{
		                	case sf::Keyboard::Space:
		                		if (strcmp(player->powerup,"JETPACK") == 0)
		                		{
									player->jetpackJump();
		                		} 
								else if (strcmp(player->powerup, "HIGHJUMP") == 0){
									player->highJump();
								}
								else {
									player->charging = true;
		                		}
		                		break;
		                	case sf::Keyboard::D:
				            	player->faceLeft = false;
				            	player->moveLeft = true;
		                    		break;
		                	case sf::Keyboard::A:
				            	player->moveRight = true;
				            	player->faceLeft = true;
		                    		break;
		            	}

		        }

		        // key release events
		        if(Event.type == sf::Event::KeyReleased)
		        {
					//std::cout << Event.key.code << std::endl;
		            switch(Event.key.code)
		            {
		                case sf::Keyboard::Space:
		                    if (strcmp(player->powerup,"JETPACK") != 0)
		                    {
		                        player->charging = false;
		                        player->jump();
		                        manager->queueEvent(&jump);
		                    }
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
	}

	void GameView::draw()
	{
		window->clear(sf::Color::Black);
		sf::Vector2f position(0, 0);
		position.y = player->getY() + 20 - (250);
		//std::cout << position.y << std::endl;
		//draw background
		background.setPosition(sf::Vector2f(position.x, position.y));
		background.setTextureRect(sf::IntRect(position.x, position.y, window->getSize().x, window->getSize().y));
		window->draw(background);

		lifeSprite.setPosition(650, player->getY() + 20 - (250) + 20 + 20);
		lifeSprite.setTextureRect(sf::IntRect(0, 0, 16 * (player->life + 1), 16));
		lifeSprite.setScale(2.0f, 2.0f);
		window->draw(lifeSprite);

		// draw platforms
		for (auto &platform : *level->getPlatforms())
		{
			platform->render(window);
		}

		// draw powerups
		for (auto *powerup : *level->getPowerups())
		{
			powerup->render(window);
		}

		// draw hazards
		for (auto *hazard : *level->getFallingHazards())
		{
			hazard->render(window);
		}

		for (auto *fireball : *level->getFireballs())
		{
			fireball->render(window);
		}

		// draw player
		player->render(window);

		// draw charge bar
		drawChargeBar();

		// draw lava
		lavaSprite.setPosition(sf::Vector2f(-600, level->getLavaY()));
		window->draw(lavaSprite);

		// draw score
		text.setPosition(sf::Vector2f(position.x + 20, position.y - 10));
		std::string scores = static_cast<std::ostringstream*>(&(std::ostringstream() << player->score))->str();
		text.setString(scores);
		window->draw(text);

		view.reset(sf::FloatRect(position.x, position.y, 800, 600));

		if ((level->getLavaY() - player->getY() < 300))
		{
		    shakeScreen();
		    if (earthquakeSound.getStatus() == 0)
		    {
			manager->queueEvent(&earthquake);
		    }
		}
		else if (level->getLavaY() - player->getY() > 300)
		{
		    earthquakeSound.stop();
		}

		window->setView(view);
    }

    void GameView::shakeScreen()
    {
        int seed;
        seed = rand() % 100;
        if (seed <= 49)
        {
            view.rotate(1);
        }
        else
        {
            view.rotate(-1);
        }
    }

     void GameView::respond(const EventInterface& events)
     {
	if (events.getEventType() == GameOverEvent::eventId)
	{
		isGameover = true;
		isPlaying = false;
		gamePlayMusic.stop();
		manager->queueEvent(&loser);
	}
        else if (events.getEventType() == GameStartEvent::eventId)
        {
            isPlaying = false;
            isGameover = false;
            isWait = true;
            gameOverSound.stop();
            manager->queueEvent(&startMusic);
        }
        else if (events.getEventType() == GamePlayEvent::eventId)
        {
            isPlaying = true;
            isGameover = false;
            isWait = false;
            gameOverSound.stop();
            startScreenMusic.stop();
            manager->queueEvent(&playingMusic);
        }
        else if (events.getEventType() == GamePauseEvent::eventId)
        {
            isWait = true;
            gamePlayMusic.stop();
            jumpSound.stop();
            manager->queueEvent(&pauseMusic);
        }
        else if (events.getEventType() == GameRestartEvent::eventId)
        {
            isPlaying = false;
            isGameover = false;
            isWait = true;
            gameOverSound.stop();
            manager->queueEvent(&startMusic);
        }
	else if ((events.getEventType() == EarthquakeSoundEvent::eventId) && (isWait == false))
        {
            earthquakeSound.play();
        }
        else if ((events.getEventType() == HitByFallingHazardEvent::eventId))
        {
            	hazardSound.play();
		player->isHit = true;
        }
        else if (events.getEventType() == PlayMusicEvent::eventId)
        {
            gamePlayMusic.play();
        }
        else if (events.getEventType() == StartSoundEvent::eventId)
        {
            startScreenMusic.play();
        }
        else if ((events.getEventType() == JumpSoundEvent::eventId) && (isPlaying == true) && (isWait == false))
        {
            jumpSound.play();
        }
        else if ((events.getEventType() == PauseSoundEvent::eventId) && (isWait == true) && (isGameover == false))
        {
            pauseScreenMusic.play();
        }
        else if ((events.getEventType() == GameOverSoundEvent::eventId) && (isGameover == true))
        {
            earthquakeSound.stop();
            gamePlayMusic.stop();
			localscores->load("Highscores.txt");
			LocalScoreboard::Entry entry;
			entry.setName("You!");
			entry.score = player->score;
			localscores->addEntry(entry);
			localscores->prune(5);
			localscores->save("Highscores.txt");
			highscorelist.clear();

            gameOverSound.play();
        }
        /*
	else
        {
		std::cout << "UNKOWN EVENT \n";
	}
	*/
     }
}
