#include "ScoreBoard.hpp"

void ScoreBoard::sendInformation(char* message){
	sf::IpAddress ip("127.0.0.1");
	sf::UdpSocket socket;
	sf::Packet packet;

	packet.append(message, strlen(message));
	socket.send(packet, ip, 9000);
}