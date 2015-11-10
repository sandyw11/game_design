#include <SFML/Graphics.hpp>
#include <vector>
#include "GameLogic.hpp"
#include "GameView.hpp"
#include "Platform.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "EventManager.hpp"
#include "ActorDestroyedEvent.hpp"
#include <ctime>
//#include "boost\bind.hpp"
<<<<<<< HEAD
=======

>>>>>>> master

int main(int argc, char** argv)
{
	// create main window
	lava::eventManager eventManager;
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 800, 600));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	sf::RenderWindow window(sf::VideoMode(800,600,32), "Lava Leaper");
	window.setView(view);
	sf::Clock clock;
  
	// create player and level
	lava::Player player;
	lava::Level level(std::time(NULL));

	// init game view and logic
	lava::GameView gameView(&window, &level, &player, view);
	lava::GameLogic gameLogic(&level, &player);

	/*
	EventDelegate delegates = std::bind(&lava::GameLogic::respond, &gameLogic, std::placeholders::_1);
	EventDelegate delegates2 = std::bind(&lava::GameView::respond, &gameView, std::placeholders::_1);
	//method_hash pairID(reinterpret_cast < intptr_t > (&gameLogic), reinterpret_cast <intptr_t> (&lava::GameLogic::respond));
	ActorDestroyedEvent events;
	ActorDestroyedEvent* pointer = &events;
	eventManager.enterMapValue(ActorDestroyedEvent::eventId, events);
	eventManager.registerEvent(delegates, events);
	eventManager.registerEvent(delegates2, events);
	eventManager.registerEvent(delegates2, events);
	eventManager.queueEvent(pointer);*/
	// start main loop
	while(window.isOpen())
	{
		//eventManager.queueEvent(pointer);
		float delta = clock.restart().asSeconds();
		gameLogic.update(delta);
		gameView.update(clock);
		//eventManager.processEvents();
	}
    
	// Done.
	return 0;
}
