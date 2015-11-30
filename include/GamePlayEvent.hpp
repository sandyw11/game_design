#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "EventInterface.hpp"

class GamePlayEvent: public EventInterface {

public:
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const { return timeStamp; }

};
#endif
//const int GamePlayEvent::eventId = int(&GamePlayEvent::eventId);
//const int GamePlayEvent::eventId = (int)(&GamePlayEvent::eventId);
