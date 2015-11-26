#ifndef JUMPSOUNDEVENT_HPP
#define JUMPSOUNDEVENT_HPP

#include "EventInterface.hpp"

class JumpSoundEvent : public EventInterface{

public:
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const {return timeStamp;}

};

//const int JumpSoundEvent::eventId = int(&JumpSoundEvent::eventId);
//const int JumpSoundEvent::eventId = (int)(&JumpSoundEvent::eventId);
#endif // JUMPSOUNDEVENT_HPP
