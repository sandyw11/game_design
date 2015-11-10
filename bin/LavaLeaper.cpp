#include <SFML/Graphics.hpp>
#include <vector>
#include "GameLogic.hpp"
#include "GameView.hpp"
#include "GameGUI.hpp"
#include "Platform.hpp"

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow window(sf::VideoMode(800,600,32), "Lava Leaper");    
  sf::Clock clock;
  
  // add player to entities
  std::vector<lava::Actor*> actors;
  lava::Player player;
  actors.push_back(&player);
  
  // init game view and logic
  lava::GameView gameView(&window, &actors, &player);
  lava::GameLogic gameLogic(&actors, &player);

  // start main loop
    while(window.isOpen())
    {
        float delta = clock.restart().asSeconds();
        gameLogic.update(delta);
        gameView.update(clock);
    }
    
    // Done.
  return 0;
}
