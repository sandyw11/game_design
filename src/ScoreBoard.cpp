#include "ScoreBoard.hpp"
#include <algorithm>
#include <fstream>

void ScoreBoard::sendInformation(char* message){
	sf::UdpSocket socket;
	sf::Packet packet;

	packet.append(message, strlen(message));
	socket.send(packet, this->ip, 9000);
}

ScoreBoard::ScoreBoard() {
	this->ip = sf::IpAddress("100.96.11.106");
}

void ScoreBoard::makePacket(const wchar_t* action, std::wstring name,  float score, sf::Packet &packet)
{
	JSONObject data;
	data[L"action"] = new JSONValue(action);
	data[L"name"] = new JSONValue(name);
	data[L"score"] = new JSONValue(score);

	JSONValue * val = new JSONValue(data);
	data.clear();

	std::wstring dataString = val->Stringify();
	delete val;

	std::string notSoWide;
	notSoWide.assign(dataString.begin(), dataString.end());

	packet.append(notSoWide.c_str(), notSoWide.length());
}

void ScoreBoard::addEntry(std::wstring name, float score) {
	sf::UdpSocket socket;
	sf::Packet packet;

	makePacket(L"AddScore",name , score, packet);

	unsigned short port = 1000;

	if (socket.send(packet, this->ip, port) != sf::Socket::Done)
	{
		std::cout << "An error ocurred sending packet" << std::endl;
	}

}

JSONValue *ScoreBoard::getEntry() {
	sf::UdpSocket socket;
	sf::Packet packet;
	unsigned short port = 1000;
	unsigned short respPort = 1001;
	//No arguments means program should retrieve scores and print them
	makePacket(L"GetScores", L"", 0.0f, packet);
	socket.bind(respPort);
	socket.send(packet, this->ip, port);

	char buffer[512];      // The buffer to store raw response data in
	sf::IpAddress respIP;  // The ip address where the response came from
	size_t respSize;     // The amount of data actually written to buffer

	// Now receive a response.  This is a blocking call, meaning your program
	// will hang until a response is received.
	socket.receive(buffer, 512, respSize, respIP, port);

	std::string respString(buffer, respSize);

	JSONValue * jsonHighScores = JSON::Parse(respString.c_str());
	if (!jsonHighScores->IsObject())
	{
		std::cout << "Something went wrong, not good.";
	}

	return jsonHighScores;
}

