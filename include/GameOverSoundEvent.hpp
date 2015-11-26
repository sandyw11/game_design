#ifndef GAMEOVERSOUNDEVENT_HPP
#define GAMEOVERSOUNDEVENT_HPP


#include "EventInterface.hpp"

class GameOverSoundEvent : public EventInterface{

public:
	int timeStamp;
	static const int eventId;
	int getEventType(void) const { return eventId; }
	virtual float getTimeStamp(void) const {return timeStamp;}

};

#endif // GAMEOVERSOUNDEVENT_HPP
