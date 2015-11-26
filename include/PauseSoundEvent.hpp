#ifndef PAUSESOUNDEVENT_HPP
#define PAUSESOUNDEVENT_HPP
#include "EventInterface.hpp"

class PauseSoundEvent : public EventInterface{

public:
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const {return timeStamp;}

};

//const int PauseSoundEvent::eventId = int(&PauseSoundEvent::eventId);
//const int PauseSoundEvent::eventId = (int)(&PauseSoundEvent::eventId);
#endif // PAUSESOUNDEVENT_HPP
