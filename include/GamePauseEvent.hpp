#ifndef GAMEPAUSE_HPP
#define GAMEPAUSE_HPP

#include "EventInterface.hpp"

class GamePauseEvent: public EventInterface {

public:
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const { return timeStamp; }

};
#endif
//const int GamePauseEvent::eventId = int(&GamePauseEvent::eventId);
//const int GamePauseEvent::eventId = (int)(&GamePauseEvent::eventId);
