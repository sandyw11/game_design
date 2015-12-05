#ifndef GAMESTART_HPP
#define GAMESTART_HPP

#include "EventInterface.hpp"

class GameStartEvent: public EventInterface {

public:
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const { return timeStamp; }

};
#endif
//const int GameStartEvent::eventId = int(&GameStartEvent::eventId);
//const int GameStartEvent::eventId = (int)(&GameStartEvent::eventId);
