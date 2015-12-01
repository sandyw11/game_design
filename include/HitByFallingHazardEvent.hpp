#ifndef HITBYFALLINGHAZARDEVENT_HPP
#define HITBYFALLINGHAZARDEVENT_HPP

#include "EventInterface.hpp"

class HitByFallingHazardEvent : public EventInterface{

public:
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const { return timeStamp; }
};

//const int HitByFallingHazardEvent::eventId = int(&HitByFallingHazardEvent::eventId);
//const int HitByFallingHazardEvent::eventId = (int)(&HitByFallingHazardEvent::eventId);
#endif
