#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <SFML/Network.hpp>
#include "JSON.h"
#include "JSONValue.h"
#include <string.h>
#include <cstring>
#include <vector>
#include <utility>
#include <iostream>

#define DESC_LENGTH	50

class ScoreBoard{
public:
	ScoreBoard();

	void makePacket(const wchar_t* action, std::wstring name, float score, sf::Packet &packet);
	JSONValue *getEntry();

	bool load(char const* data_file);
	bool save(char const* data_file) const;

	void addEntry(std::wstring name, float score);
	//Entry getEntry(int index) const;
	void sendInformation(char* message);
private:
	//Not copy-constructable
	ScoreBoard(ScoreBoard const&);
	sf::IpAddress ip;



};

#endif