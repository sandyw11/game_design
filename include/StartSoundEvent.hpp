#ifndef STARTSOUNDEVENT_HPP
#define STARTSOUNDEVENT_HPP


#include "EventInterface.hpp"

class StartSoundEvent : public EventInterface{

public:
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const {return timeStamp;}

};

//const int StartSoundEvent::eventId = int(&StartSoundEvent::eventId);
//const int StartSoundEvent::eventId = (int)(&StartSoundEvent::eventId);
#endif // STARTSOUNDEVENT_HPP
