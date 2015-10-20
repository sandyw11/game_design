#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "GameLogic.hpp"

#include "Platform.hpp"

namespace lava
{
	class GameView
	{
	public:
		GameView(sf::RenderWindow* window, std::vector<Actor*>* actors, Player* player);
        void update(sf::Clock clock);
                
        void setFont();
        void setPauseMessage();
        void setPause();
        void setStartMessage();
        void setStart();
        void setGameoverMessage();
        void setGameover();
		
	protected:
		sf::RenderWindow* window;
        void processInput(sf::Clock clock);
		void draw();
	
	private:
		std::vector<Actor*>* actors;
		Player* player;
        sf::Font font;
        bool isWait = false;
        bool isPlaying = false;
        bool isGameover = false;
        
	};
}

#endif