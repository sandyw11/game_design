#ifndef GAME_GUI_HPP
#define GAME_GUI_HPP

#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEM 3

namespace lava
{
    class GameGUI
	{
	public:
        GameGUI(float width, float height);
        ~GameGUI();
        
        void draw(sf::RenderWindow *window);
        void MoveUp();
        void MoveDown();
        int GetPressedItem() { return selectedItemIndex; }
        sf::Font font;
        
    private:
        int selectedItemIndex;
        sf::Text menu[MAX_NUMBER_OF_ITEM];
    };
}

#endif