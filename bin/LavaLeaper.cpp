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
#include "ScoreBoard.hpp"
#include"JSON.h"
#include <ctime>

int main(int argc, char** argv)
{
	// create main window
	//ScoreBoard scores;
	//JSONValue *jsonHighScores;
	//char* message = "bob";
	//char *score = "1000";
	//std::wstring something = std::wstring(message, message + std::strlen(message));
	//scores.sendInformation(message);
	//scores.addEntry(something, score);
	//scores.addEntry(something, "2222");
	//jsonHighScores = scores.getEntry();


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
	sf::Texture lavaTexture;
	sf::Texture backgroundTexture;
	if (!playerTexture.loadFromFile("graph/Guy.png"))
	{
		std::cout << "Cannot load Player image" << std::endl;
	}
	if (!platformTexture.loadFromFile("graph/Platform.png"))
	{
		std::cout << "Cannot load Platform image" << std::endl;
	}
	if (!lavaTexture.loadFromFile("graph/Lava.png"))
	{
		std::cout << "Cannot load Lava image" << std::endl;
	}
	if (!backgroundTexture.loadFromFile("graph/volcanic_underground_background.png"))
	{
		std::cout << "Cannot load Background image" << std::endl;
	}
	platformTexture.setRepeated(true);
	lavaTexture.setRepeated(true);
	backgroundTexture.setRepeated(true);

	// create player and level
	lava::Player player(&playerTexture, &eventManager);
	lava::Level level(std::time(NULL),&platformTexture, &eventManager);

	GameOverEvent event;
	eventManager.enterMapValue(GameOverEvent::eventId, event);

	// init game view and logic
	lava::GameView gameView(&window, &level, &player, view, &lavaTexture,&backgroundTexture,&eventManager);
	lava::GameLogic gameLogic(&level, &player, &eventManager);

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
