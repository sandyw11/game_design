#ifndef EVENTINTERFACE_HPP
#define EVENTINTERFACE_HPP

class EventInterface{
public:
	static const int eventId;
	const int& getEventType(void) const {return eventId;}
	virtual float getTimeStamp(void) const = 0;
	bool operator==(const EventInterface &other) const{
		return eventId == other.eventId;
	}
};

#endif