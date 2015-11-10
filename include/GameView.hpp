#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "GameLogic.hpp"
<<<<<<< HEAD
#include "Platform.hpp"

=======
>>>>>>> origin/game-state

namespace lava
{
	class GameView
	{
	public:
		GameView(sf::RenderWindow* window, std::vector<Actor*>* actors, Player* player);
        ~GameView();
        void update(sf::Clock clock);
        
<<<<<<< HEAD
=======
        void setInstructionMessage();
        void setInstruction();
>>>>>>> origin/game-state
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
<<<<<<< HEAD

=======
        
>>>>>>> origin/game-state
        bool isWait = false;
        bool isPlaying = false;
        bool isGameover = false;
        
	};
}

#endif
