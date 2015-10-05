#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"
#include "GameView.hpp"

int main(int argc, char** argv)
{
  lava::GameView gameView;
  lava::GameLogic gameLogic;
  
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Lava Leaper");
  sf::Clock clock;

  // start main loop
  while(App.isOpen())
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
