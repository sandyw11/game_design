#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.hpp"

namespace lava
{
	class GameView
	{
	public:
		void update(float delta);
		GameView(sf::RenderWindow* window, std::vector<Actor*>* actors, Player* player);
		
	protected:
		sf::RenderWindow* window;
		void processInput();
		void draw();
	
	private:
		std::vector<Actor*>* actors;
		Player* player;
	};
}

#endif