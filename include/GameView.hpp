#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Actor.hpp"

namespace lava
{
	class GameView
	{
	public:
		void update(float delta);
		GameView(sf::RenderWindow* window, std::vector<Actor*>* actors);
		
	protected:
		sf::RenderWindow* window;
		std::vector<Actor*>* actors;
		void processInput();
		void draw();
	};
}

#endif