#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include "EventInterface.hpp"

class GameOverEvent: public EventInterface {

public:
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const { return timeStamp; }

};
#endif
//const int ActorDestroyedEvent::eventId = int(&ActorDestroyedEvent::eventId);
//const int ActorDestroyedEvent::eventId = (int)(&ActorDestroyedEvent::eventId);