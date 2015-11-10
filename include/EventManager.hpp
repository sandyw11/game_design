#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <stdlib.h>
#include "EventInterface.hpp"
#include <list>
#include <set>
#include <functional>
#include <iostream>
#include <map>
//#include "boost\function.hpp"
//#include "boost\range\algorithm\find.hpp"
//#include "boost\function_equal.hpp"

typedef std::function<void(const EventInterface&)> EventDelegate;
typedef std::pair < intptr_t, intptr_t > method_hash;
typedef std::list<method_hash> position_list;
typedef std::list<const EventInterface*> event_queue;
typedef std::list<EventDelegate> delegates_list;
typedef std::map<int, delegates_list> event_map;

namespace lava{
	class eventManager{
	protected:
		event_queue queues[2];
		event_queue* process_queue;
		event_queue* register_queue;
		event_map eventDelegateMap;
	public:
		eventManager();
		virtual void queueEvent(const EventInterface* events);
		virtual void enterMapValue(int key, const EventInterface& event);
		virtual void registerEvent(EventDelegate& d, EventInterface& events);
		virtual void executeEvent(const EventInterface& events);
		virtual void removeEvent(const EventInterface* events);
		virtual void processEvents(void);

	};
}
#endif