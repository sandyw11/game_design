#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "GameLogic.hpp"
#include "GameOverEvent.hpp"
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
#include <SFML/Audio.hpp>

namespace lava
{
	class GameView
	{
	public:
		GameView(sf::RenderWindow* window, Level* level, Player* player, sf::View view,sf::Texture *lavaTexture, sf::Texture *backgroundTexture, lava::eventManager *manager);
        void update(sf::Clock clock);

        void setInstructionMessage();
        void setInstruction();
        void playSound(const char* soundName);
        void stopSound();
        void setPauseMessage();
        void setPause();
        void setStartMessage();
        void setStart();
        void setGameoverMessage();
        void setGameover();
		void respond(const EventInterface& events);
		void shakeScreen();
		void playMusic(const char* musicName);
		void playNonLoopSound(const char* noLoopSoundName);

		GameOverEvent gameOver;
		EarthquakeSoundEvent earthquake;
		PlayMusicEvent playingMusic;
		JSONValue *jsonHighScores;
		ScoreBoard scores;
		JumpSoundEvent jump;
		GameOverSoundEvent loser;
		StartSoundEvent startMusic;
		PauseSoundEvent pauseMusic;

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
		sf::SoundBuffer noLoopBuffer;
		sf::Sound noLoopSound;
        bool isWait;
        bool isPlaying;
        bool isGameover;
        bool soundPlaying;
        bool musicPlaying;

        //sf::RectangleShape lava;
		sf::Sprite background;
		sf::Sprite lavaSprite;
		sf::View view;
	};
}

#endif
