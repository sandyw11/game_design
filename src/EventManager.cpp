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
		eventManager::eventDelegateMap[key] = newDelegates;
	}
	void eventManager::queueEvent(const EventInterface* event){
		eventManager::register_queue->push_back(event);
	}
	void eventManager::registerEvent(EventDelegate& d, EventInterface& events){
		//std::cout << eventManager::eventDelegateMap.size();
		std::cout << events.getEventType();
		std::cout << "\n";
		int temp = events.getEventType();
		eventManager::enterMapValue(events.getEventType(), events);
		delegates_list delegates = eventManager::eventDelegateMap[events.getEventType()];
		//std::cout << events.getEventType();

		//auto findIter = std::find(delegates.begin(),delegates.end(), d);
		//if (findIter == delegates.end()){
		//auto findIter = delegates.end();
		delegates.push_back(d); 
		if (delegates.empty()){
			std::cout << "Empty\n";
		}
		else{
			std::cout << "Not Empty\n";
		}
		//}
	}
	void eventManager::executeEvent(const EventInterface& events) { 
		auto delegatelist = eventManager::eventDelegateMap.find(events.getEventType());
		if (delegatelist == eventManager::eventDelegateMap.end()){
			return;
		}
		std::cout << "\n";
		std::cout << events.getEventType();
		delegates_list delegates = eventManager::eventDelegateMap[events.getEventType()];
		std::cout << delegates.size();
		for (auto current = delegates.begin(); current != delegates.end(); current++){
			(*current)(events);
		}

	}
	void eventManager::removeEvent(const EventInterface* events){

	}
	void eventManager::processEvents(void){
		std::swap(process_queue, register_queue);
		register_queue->clear();
		//std::cout << register_queue->size();
 		while (!process_queue->empty()){
			const EventInterface* currentEvent = process_queue->front();
			process_queue->pop_front();
			executeEvent(*currentEvent);
		}
	}
}