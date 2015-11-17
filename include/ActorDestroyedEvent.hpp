#ifndef ACTORDESTROYED_HPP
#define ACTORDESTROYED_HPP

#include "EventInterface.hpp"

class ActorDestroyedEvent : public EventInterface{

public: 
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const {return timeStamp;}

};

//const int ActorDestroyedEvent::eventId = int(&ActorDestroyedEvent::eventId);
//const int ActorDestroyedEvent::eventId = (int)(&ActorDestroyedEvent::eventId);
#endif