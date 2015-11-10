#ifndef EVENTDELEGATE_HPP
#define EVENTDELEGATE_HPP

#include "EventInterface.hpp"
#include <functional>

class EventDelegate{
	const int delegateId;
	std::function<void(const EventInterface&)> callback;

	bool operator==(const EventDelegate &other) const{
		return delegateId == other.delegateId;
	}
};

#endif