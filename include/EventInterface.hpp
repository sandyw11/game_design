#ifndef EVENTINTERFACE_HPP
#define EVENTINTERFACE_HPP

class EventInterface{
public:
	//static const int eventId;
	int eventId;
	virtual int getEventType(void) const = 0;
	virtual float getTimeStamp(void) const = 0;
	//bool operator==(const EventInterface &other) const{
	//	return eventId == other.eventId;
	//}
};

#endif