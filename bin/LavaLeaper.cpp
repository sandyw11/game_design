#include <SFML/Graphics.hpp>
#include <vector>
#include "GameLogic.hpp"
#include "GameView.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "EventManager.hpp"
#include "ActorDestroyedEvent.hpp"
#include "GameOverEvent.hpp"
#include "GameStartEvent.hpp"
#include "GamePlayEvent.hpp"
#include "GamePauseEvent.hpp"
#include "GameRestartEvent.hpp"
#include "EventDelegate.hpp"
#include "ScoreBoard.hpp"
#include "JSON.h"
#include "EarthquakeSoundEvent.hpp"
#include "PlayMusicEvent.hpp"
#include "JumpSoundEvent.hpp"
#include "GameOverSoundEvent.hpp"
#include "StartSoundEvent.hpp"
#include "PauseSoundEvent.hpp"
#include "LocalScoreBoard.hpp"
#include <ctime>

int main(int argc, char** argv)
{
	// create main window
	LocalScoreboard scores;
	//JSONValue *jsonHighScores;
	//char* message = " Hello bob";
	//char *score = "1000";
	//sf::IpAddress ip("127.0.0.1");
	//sf::UdpSocket socket;
	//sf::Packet packet;

	//packet.append(message, std::strlen(message));
	//socket.send(packet, ip, 9000);
	//std::wstring something = std::wstring(message, message + std::strlen(message));
	//scores.sendInformation(message);
	//scores.addEntry(something, score);
	//scores.addEntry(something, "2222");
	//jsonHighScores = scores.getEntry();
	/*sf::UdpSocket socket;
	sf::Packet packet;
	unsigned short port = 5400;
	unsigned short respPort = 5401;
	//No arguments means program should retrieve scores and print them
	scores.makePacket(L"GetScores", L"", 0.0f, packet);
	socket.bind(socket.getLocalPort());
	socket.send(packet,sf::IpAddress("127.0.0.1"), port);
	//std::cout << sf::IpAddress::getLocalAddress() << std::endl;
	char buffer[512];      // The buffer to store raw response data in
	sf::IpAddress respIP;  // The ip address where the response came from
	size_t respSize;     // The amount of data actually written to buffer
	unsigned short yport;
	// Now receive a response.  This is a blocking call, meaning your program
	// will hang until a response is received.
	//socket.setBlocking(false);
	socket.receive(buffer, 512, respSize, respIP, port);

	std::string respString(buffer, respSize);

	JSONValue * jsonHighScores = JSON::Parse(respString.c_str());
	if (!jsonHighScores->IsObject())
	{
		std::cout << "Something went wrong, not good.";
	}
	std::cout << "Received " << respSize << " bytes from " << respIP << " on port " << port << std::endl;
	std::string highscorelist;
	//jsonHighScores = scores.getEntry();
	JSONObject root = jsonHighScores->AsObject();
	if (root.find(L"Scores") != root.end() && root[L"Scores"]->IsArray())
	{
		JSONArray scores = root[L"Scores"]->AsArray();
		for (int i = 0; i < scores.size(); i++)
		{
			JSONObject curObj = scores[i]->AsObject();
			std::string notSoWide;
			std::string score = static_cast<std::ostringstream*>(&(std::ostringstream() << curObj[L"Score"]->AsNumber()))->str();
			std::string rank = static_cast<std::ostringstream*>(&(std::ostringstream() << i + 1))->str();
			notSoWide.assign(curObj[L"Name"]->AsString().begin(), curObj[L"Name"]->AsString().end());
			highscorelist += "Rank " + rank + "  Name: " + notSoWide + "  High Score: " + score + "\n";
		}
	}
	std::cout << highscorelist << std::endl;*/
	
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
	sf::Texture hazardTextures;
	sf::Texture lifeTexture;

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
	if (!backgroundTexture.loadFromFile("graph/background.png"))
	{
		std::cout << "Cannot load Background image" << std::endl;
	}
	if (!hazardTextures.loadFromFile("graph/P&H.png"))
	{
		std::cout << "Cannot load Hazard and Power up images" << std::endl;
	}
	if (!lifeTexture.loadFromFile("graph/Life.png"))
	{
		std::cout << "Cannot load Life images" << std::endl;
	}
	srand(time(NULL));
	platformTexture.setRepeated(true);
	lavaTexture.setRepeated(true);
	backgroundTexture.setRepeated(true);
	lifeTexture.setRepeated(true);
	// create player and level
	lava::Player player(&playerTexture, &eventManager);
	lava::Level level(std::time(NULL),&platformTexture, &hazardTextures, &eventManager);

	GameOverEvent event;
	GameStartEvent gameStart;
	GamePlayEvent gamePlay;
	GamePauseEvent gamePause;
	GameRestartEvent gameRestart;
	EarthquakeSoundEvent earthquake;
	PlayMusicEvent playingMusic;
	JumpSoundEvent jump;
	GameOverSoundEvent loser;
	StartSoundEvent startMusic;
	PauseSoundEvent pauseMusic;

	eventManager.enterMapValue(GameOverEvent::eventId, event);
	eventManager.enterMapValue(GameStartEvent::eventId, gameStart);
	eventManager.enterMapValue(GamePlayEvent::eventId, gamePlay);
	eventManager.enterMapValue(GamePauseEvent::eventId, gamePause);
	eventManager.enterMapValue(GameRestartEvent::eventId, gameRestart);
	eventManager.enterMapValue(EarthquakeSoundEvent::eventId, earthquake);
	eventManager.enterMapValue(PlayMusicEvent::eventId, playingMusic);
	eventManager.enterMapValue(JumpSoundEvent::eventId, jump);
	eventManager.enterMapValue(GameOverSoundEvent::eventId, loser);
	eventManager.enterMapValue(StartSoundEvent::eventId, startMusic);
	eventManager.enterMapValue(PauseSoundEvent::eventId, pauseMusic);

	// init game view and logic
	lava::GameView gameView(&window, &level, &player, view, &lavaTexture,&backgroundTexture,&lifeTexture,&eventManager, &scores);
	lava::GameLogic gameLogic(&level, &player, &eventManager);

	// start main loop
	while(window.isOpen())
	{
		float delta = clock.restart().asSeconds();
		gameView.update(clock);
		gameLogic.update(delta);
		eventManager.processEvents();
	}

	// Done.*/
	return 0;
}
