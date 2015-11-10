#include "EventManager.hpp"

//bool operator==(const EventDelegate &a, const EventDelegate &b){
//	if (a)
//}
namespace lava{
	eventManager::eventManager(){
		this->register_queue = &eventManager::queues[0];
		this->process_queue = &eventManager::queues[1];
	}
	void eventManager::enterMapValue(int key, const EventInterface& event){
		delegates_list newDelegates;
		//eventManager::eventDelegateMap[key] = newDelegates;
		eventManager::eventDelegateMap.insert(std::pair<int, delegates_list>(key, newDelegates));
	}
	void eventManager::queueEvent(const EventInterface* event){
		eventManager::register_queue->push_back(event);
	}
	void eventManager::registerEvent(EventDelegate& d, EventInterface& events){
		delegates_list delegates = eventManager::eventDelegateMap[events.getEventType()];
		//std::cout << delegates.size() << std::endl;
		//std::cout << events.getEventType() << std::endl;
		//auto findIter = std::find(delegates.begin(),delegates.end(), d);
		//if (findIter == delegates.end()){
		//	auto findIter = delegates.end();
		//}
		delegates.push_back(d);
		//eventManager::eventDelegateMap.insert(std::pair<int, delegates_list>(events.getEventType(),delegates));
		eventManager::eventDelegateMap[events.getEventType()] = delegates;
		//}
	}
	void eventManager::executeEvent(const EventInterface& events) { 
		auto delegatelist = eventManager::eventDelegateMap.find(events.getEventType());
		if (delegatelist == eventManager::eventDelegateMap.end()){
			return;
		}
		delegates_list delegates = eventManager::eventDelegateMap[events.getEventType()];
		for (auto current = delegates.begin(); current != delegates.end(); current++){
			(*current)(events);
		}

	}
	void eventManager::removeEvent(const EventInterface* events){

	}
	void eventManager::processEvents(void){
		std::swap(process_queue, register_queue);
		register_queue->clear();
 		while (!process_queue->empty()){
			const EventInterface* currentEvent = process_queue->front();
			process_queue->pop_front();
			executeEvent(*currentEvent);
		}
	}
}