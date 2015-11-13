#ifndef EVENTDELEGATE_HPP
#define EVENTDELEGATE_HPP

#include "EventInterface.hpp"
#include <functional>

class EventDelegate{
public:
	EventDelegate();
	EventDelegate(std::function<void(const EventInterface&)> input, int ID);
	int delegateId;
	std::function<void(const EventInterface&)> callback;

	bool operator==(EventDelegate &other) const{
		return delegateId == other.delegateId;
	}

	bool operator!=(EventDelegate &other) const{
		return delegateId != other.delegateId;
	}
};

#endif