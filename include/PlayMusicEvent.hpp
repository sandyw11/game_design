#ifndef PLAYMUSICEVENT_HPP
#define PLAYMUSICEVENT_HPP

#include "EventInterface.hpp"

class PlayMusicEvent: public EventInterface {

public:
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const { return timeStamp; }

};
#endif
//const int PlayMusicEvent::eventId = int(&PlayMusicEvent::eventId);
//const int PlayMusicEvent::eventId = (int)(&PlayMusicEvent::eventId);
