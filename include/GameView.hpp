#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "GameLogic.hpp"
#include "GameOverEvent.hpp"
#include "Platform.hpp"
#include "GameGUI.hpp"
#include "EventManager.hpp"

namespace lava
{
	class GameView
	{
	public:
		GameView(sf::RenderWindow* window, Level* level, Player* player, sf::View view,sf::Texture *lavaTexture, sf::Texture *backgroundTexture, lava::eventManager *manager);
        void update(sf::Clock clock);

        void setInstructionMessage();
        void setInstruction();
        
        void setPauseMessage();
        void setPause();
        void setStartMessage();
        void setStart();
        void setGameoverMessage();
        void setGameover();
		void respond(const EventInterface& events);

		GameOverEvent gameOver;
		
	protected:
		sf::RenderWindow* window;
        void processInput(sf::Clock clock);
		void draw();
	
	private:
		Level* level;
		Player* player;
		eventManager *manager;
		sf::Font font;
		sf::Text text;
        bool isWait;
        bool isPlaying;
        bool isGameover;

        //sf::RectangleShape lava;
		sf::Sprite background;
		sf::Sprite lavaSprite;
		sf::View view;
	};
}

#endif
