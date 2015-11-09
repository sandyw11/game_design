#include <SFML/Graphics.hpp>
#include <vector>
#include "GameLogic.hpp"
#include "GameView.hpp"
#include "Platform.hpp"
#include "Level.hpp"

int main(int argc, char** argv)
{
  // create main window
  sf::View view;
  view.reset(sf::FloatRect(0, 0, 800, 600));
  view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
  sf::RenderWindow window(sf::VideoMode(800,600,32), "Lava Leaper");
  window.setView(view);
  sf::Clock clock;
  
  // create player and level
  lava::Player player;
  lava::Level level(1);

  // init game view and logic
  lava::GameView gameView(&window, &level, &player);
  lava::GameLogic gameLogic(&level, &player);

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
