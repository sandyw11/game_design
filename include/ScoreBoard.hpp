#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <SFML/Network.hpp>
#include <string.h>
#include <cstring>

class ScoreBoard{
public:
	void sendInformation(char* message);
};

#endif