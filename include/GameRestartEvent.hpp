#ifndef GAMERESTART_HPP
#define GAMERESTART_HPP

#include "EventInterface.hpp"

class GameRestartEvent: public EventInterface {

public:
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const { return timeStamp; }

};
#endif
//const int GameRestartEvent::eventId = int(&GameRestartEvent::eventId);
//const int GameRestartEvent::eventId = (int)(&GameRestartEvent::eventId);
