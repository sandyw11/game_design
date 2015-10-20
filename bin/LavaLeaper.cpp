#include <SFML/Graphics.hpp>
#include <vector>
#include "GameLogic.hpp"
#include "GameView.hpp"
#include "Platform.hpp"

int main(int argc, char** argv)
{ 
  // create main window
  sf::View view;
  view.reset(sf::FloatRect(0, 0, 800, 600));
  view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
  sf::RenderWindow window(sf::VideoMode(800,600,32), "Lava Leaper");
  window.setView(view);
  sf::Clock clock;
  
  // add player to entities
  std::vector<lava::Actor*> actors;
  lava::Player player;
  actors.push_back(&player);
  
  // create some platforms
  lava::Platform platform(150, 10);
  actors.push_back(&platform);
  
  // init game view and logic
  lava::GameView gameView(&window, &actors, &player);
  lava::GameLogic gameLogic(&actors, &player);

  // start main loop
  while(window.isOpen())
  {
    float delta = clock.restart().asSeconds();
    gameLogic.update(delta);
    gameView.update(delta);
  }

  // Done.
  return 0;
}
