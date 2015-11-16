#include <SFML/Graphics.hpp>
#include <vector>
#include "GameLogic.hpp"
#include "GameView.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "EventManager.hpp"
#include "ActorDestroyedEvent.hpp"
#include "GameOverEvent.hpp"
#include "EventDelegate.hpp"
#include <ctime>

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

	//Init Sprite sheet
	sf::Texture playerTexture;
	sf::Texture platformTexture;
	if (!playerTexture.loadFromFile("Guy.png"))
	{
		std::cout << "Cannot load Player image" << std::endl;
	}
	if (!platformTexture.loadFromFile("Platform.png"))
	{
		std::cout << "Cannot load Player image" << std::endl;
	}
	platformTexture.setRepeated(true);

	// create player and level
	lava::Player player(&playerTexture);
	lava::Level level(std::time(NULL),&platformTexture);

	// init game view and logic
	lava::GameView gameView(&window, &level, &player, view);
	lava::GameLogic gameLogic(&level, &player);

	/*
	//Below is a Tutorial of The Event Manager System. Feel free to uncomment the section below and run the code and play around with it to get
	//familiar with the system! This isn't 100% perfect, but hopefully it'll work. Let me know if any problems arise.
	//Make sure to pass the Event Manager object through into your respective classes.
	//When using an event make sure to include the EVENT HPP FILES and EVENTDELEGATE hpp files, probably pass in the Event Manager hpp files too

	//Create the Events and push them to the map (DO THIS BEFORE THE GAME EVEN STARTS) 
	ActorDestroyedEvent events;
	ActorDestroyedEvent events2;
	GameOverEvent event3;

	eventManager.enterMapValue(ActorDestroyedEvent::eventId, events);
	eventManager.enterMapValue(GameOverEvent::eventId, event3);

	//BINDING!!! 
	//The first arguement takes in address of the function, the second arguement is the object address, and finally the third will save the object's
	//address for future comparisions. Comparisons are still iffy so I'd apperciate it you guys can test it out more.
	
	EventDelegate example(std::bind(&lava::GameLogic::respond, &gameLogic, std::placeholders::_1),(int) &gameLogic);
	EventDelegate example2(std::bind(&lava::GameLogic::respond, &gameLogic, std::placeholders::_1), (int)&gameLogic);
	EventDelegate example3(std::bind(&lava::GameView::respond, &gameView, std::placeholders::_1), (int)&gameView);

	//REGISTER THE EVENT WITH EACH RESPECTIVE EVENT
	//First arguement is the event Delegate, the second parameter is the event  itself
	
	eventManager.registerEvent(example, events);
	eventManager.registerEvent(example, events2);
	eventManager.registerEvent(example, event3);
	eventManager.registerEvent(example, event3);
	eventManager.registerEvent(example3, event3);

	eventManager.removeDelegate(example3, event3);

	//IF YOU WANT TO TRIGGER AN EVENT
	//Make sure to queue the event.
	eventManager.queueEvent(&event3);
	*/

	// start main loop
	while(window.isOpen())
	{
		float delta = clock.restart().asSeconds();
		gameLogic.update(delta);
		gameView.update(clock);
		eventManager.processEvents();
	}
    
	// Done.
	return 0;
}
