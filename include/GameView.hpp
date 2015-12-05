#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Level.hpp"
#include "GameOverEvent.hpp"
#include "LocalScoreBoard.hpp"
#include "GameStartEvent.hpp"
#include "GamePlayEvent.hpp"
#include "GamePauseEvent.hpp"
#include "GameRestartEvent.hpp"
#include "EarthquakeSoundEvent.hpp"
#include "Platform.hpp"
#include "GameGUI.hpp"
#include "EventManager.hpp"
#include "PlayMusicEvent.hpp"
#include "JSON.h"
#include "ScoreBoard.hpp"
#include "JumpSoundEvent.hpp"
#include "GameOverSoundEvent.hpp"
#include "StartSoundEvent.hpp"
#include "PauseSoundEvent.hpp"
#include "HitByFallingHazardEvent.hpp"
#include <ctime>
#include <SFML/Audio.hpp>

namespace lava
{
	class GameView
	{
	public:
		GameView(sf::RenderWindow* window, Level* level, Player* player, sf::View view, sf::Texture *lavaTexture, sf::Texture *backgroundTexture, sf::Texture *life, lava::eventManager *manager,
			LocalScoreboard *localscores);
		~GameView();

		void update(sf::Clock clock);

		void setInstructionMessage();
		void setPauseMessage();
		void setGameoverMessage();
		void setStart();

		void respond(const EventInterface& events);
		void shakeScreen();
		void playMusic(sf::Music);

		GameOverEvent gameOver;
		GameStartEvent gameStart;
		GamePlayEvent gamePlay;
		GamePauseEvent gamePause;
		GameRestartEvent gameRestart;
		EarthquakeSoundEvent earthquake;
		PlayMusicEvent playingMusic;
		JSONValue *jsonHighScores;
		ScoreBoard scores;
		JumpSoundEvent jump;
		GameOverSoundEvent loser;
		StartSoundEvent startMusic;
		PauseSoundEvent pauseMusic;
		HitByFallingHazardEvent hazardEvent;
		bool highscoremade;
		//char * highscorelist;

	protected:
		sf::RenderWindow* window;
        void processInput(sf::Clock clock);
		void draw();
		void drawChargeBar();

	private:
		Level* level;
		Player* player;
		eventManager *manager;
		sf::Font font;
		sf::Text text;

		sf::SoundBuffer buffer;
		sf::Sound sound;
		sf::Music music;
		std::string highscorelist;

		sf::SoundBuffer hazardBuffer;
		sf::Sound hazardSound;

		sf::SoundBuffer noLoopBuffer;
		sf::Sound noLoopSound;

		sf::SoundBuffer earthquakeBuffer;
		sf::Sound earthquakeSound;

		sf::SoundBuffer jumpBuffer;
		sf::Sound jumpSound;

		sf::SoundBuffer gameOverBuffer;
		sf::Sound gameOverSound;

		sf::Music gamePlayMusic;
		sf::Music startScreenMusic;
		sf::Music pauseScreenMusic;

		LocalScoreboard *localscores;

		bool isWait;
		bool isPlaying;
		bool isGameover;
		bool isInstruct;

		GameGUI *gameGUI;

		sf::Sprite background;
		sf::Sprite lavaSprite;
		sf::Sprite lifeSprite;
		sf::View view;
	};
}

#endif
