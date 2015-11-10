#include <SFML/Graphics.hpp>
#include "GameGUI.hpp"

namespace lava
{
    GameGUI::GameGUI(float width, float height)
    {
        font.loadFromFile("font.ttf");
        
        menu[0].setFont(font);
        menu[0].setColor(sf::Color::Red);
        menu[0].setString("Play");
        menu[0].setPosition(sf::Vector2f(width / 2 - 50, height / 2 + 50 * 1));
        
        menu[1].setFont(font);
        menu[1].setColor(sf::Color::White);
        menu[1].setString("Instruction");
        menu[1].setPosition(sf::Vector2f(width / 2 - 50, height / 2 + 50 * 2));
        
        menu[2].setFont(font);
        menu[2].setColor(sf::Color::White);
        menu[2].setString("Exit");
        menu[2].setPosition(sf::Vector2f(width / 2 - 50, height / 2 + 50 * 3));
    }
    
    GameGUI::~GameGUI()
    {
        
    }
    
    void GameGUI::draw(sf::RenderWindow *window)
    {
        sf::Texture texture;
        texture.loadFromFile("graph/menu.jpg");
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, window->getSize().x, window->getSize().y));
        window->draw(sprite);
        int i;
        for(i = 0; i < MAX_NUMBER_OF_ITEM; i++)
        {
            window->draw(menu[i]);
        }
    }
    
    void GameGUI::MoveUp()
    {
        if(selectedItemIndex - 1 >= 0)
        {
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex--;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }
    }
    
    void GameGUI::MoveDown()
    {
        if(selectedItemIndex + 1 <= MAX_NUMBER_OF_ITEM)
        {
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex++;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }
    }
}