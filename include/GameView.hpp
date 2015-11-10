#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "GameLogic.hpp"
<<<<<<< HEAD
=======

>>>>>>> master
#include "Platform.hpp"

namespace lava
{
	class GameView
	{
	public:
<<<<<<< HEAD
		GameView(sf::RenderWindow* window, std::vector<Actor*>* actors, Player* player);
        void update(sf::Clock clock);

        void setInstructionMessage();
        void setInstruction();

=======
		GameView(sf::RenderWindow* window, Level* level, Player* player, sf::View view);
        void update(sf::Clock clock);
                
        void setFont();
>>>>>>> master
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
<<<<<<< HEAD

        bool isWait;
        bool isPlaying;
        bool isGameover;
        
=======
        sf::Font font;
        bool isWait;
        bool isPlaying;
        bool isGameover;
>>>>>>> master
		sf::RectangleShape lava;
		sf::View view;
	};
}

#endif
