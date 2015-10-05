#include <SFML/Graphics.hpp>
#include <vector>
#include "GameLogic.hpp"
#include "GameView.hpp"

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
  lava::GameView gameView(&window, &actors);
  lava::GameLogic gameLogic(&actors);

  // start main loop
  while(window.isOpen())
  {
    float delta = clock.restart().asSeconds();
    gameLogic.update(delta);
    gameView.update(delta);
    
    // process events
    // sf::Event Event;
    // while(App.pollEvent(Event))
    // {
    //   // Exit
    //   if(Event.type == sf::Event::Closed)
    //     App.close();
    // }

    // // clear screen and fill with blue
    // App.clear(sf::Color::Blue);

    // // display
    // App.display();
  }

  // Done.
  return 0;
}
