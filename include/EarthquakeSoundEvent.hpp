#ifndef EARTHQUAKESOUNDEVENT_HPP
#define EARTHQUAKESOUNDEVENT_HPP


#include "EventInterface.hpp"

class EarthquakeSoundEvent : public EventInterface{

public:
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const {return timeStamp;}
};

//const int EarthquakeSoundEvent::eventId = int(&EarthquakeSoundEvent::eventId);
//const int EarthquakeSoundEvent::eventId = (int)(&EarthquakeSoundEvent::eventId);
#endif
