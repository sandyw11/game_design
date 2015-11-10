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

        void setInstructionMessage();
        void setInstruction();
        
        void setPauseMessage();
        void setPause();
        void setStartMessage();
        void setStart();
        void setGameoverMessage();
        void setGameover();
		void GameView::respond(const EventInterface& events);
		
	protected:
		sf::RenderWindow* window;
        void processInput(sf::Clock clock);
		void draw();
	
	private:
		Level* level;
		Player* player;

        bool isWait;
        bool isPlaying;
        bool isGameover;

        sf::RectangleShape lava;
		sf::View view;
	};
}

#endif
