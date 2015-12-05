#include "EventManager.hpp"

/*
//Below is a Tutorial of The Event Manager System. Feel free to uncomment the section below and run the code and play around with it to get
//familiar with the system! This isn't 100% perfect, but hopefully it'll work. Let me know if any problems arise.
//Make sure to pass the Event Manager object through into your respective classes.
//When using an event make sure to include the EVENT HPP FILES and EVENTDELEGATE hpp files, probably pass in the Event Manager hpp files too

//Create the Events and push them to the map (DO THIS BEFORE THE GAME EVEN STARTS)
ActorDestroyedEvent events;
ActorDestroyedEvent events2;
GameOverEvent event3;

eventManager.enterMapValue(ActorDestroyedEvent::eventId, events);
eventManager.enterMapValue(GameOverEvent::eventId, event3);

//BINDING!!!
//The first arguement takes in address of the function, the second arguement is the object address, and finally the third will save the object's
//address for future comparisions. Comparisons are still iffy so I'd apperciate it you guys can test it out more.

EventDelegate example(std::bind(&lava::GameLogic::respond, &gameLogic, std::placeholders::_1),(int) &gameLogic);
EventDelegate example2(std::bind(&lava::GameLogic::respond, &gameLogic, std::placeholders::_1), (int)&gameLogic);
EventDelegate example3(std::bind(&lava::GameView::respond, &gameView, std::placeholders::_1), (int)&gameView);

//REGISTER THE EVENT WITH EACH RESPECTIVE EVENT
//First arguement is the event Delegate, the second parameter is the event  itself

eventManager.registerEvent(example, events);
eventManager.registerEvent(example, events2);
eventManager.registerEvent(example, event3);
eventManager.registerEvent(example, event3);
eventManager.registerEvent(example3, event3);

eventManager.removeDelegate(example3, event3);

//IF YOU WANT TO TRIGGER AN EVENT
//Make sure to queue the event.
eventManager.queueEvent(&event3);
*/

namespace lava {
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
		//auto findIter = std::find(delegates.begin(),delegates.end(), d);
		int last = 0;
		auto first = delegates.begin();
		while (first != delegates.end()){
			if (*first == d){
				break;
			}
			++first;
		}
		if (first == delegates.end()){
			delegates.push_back(d);
		}
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
			(current->callback)(events);
		}

	}
	void eventManager::removeDelegate(EventDelegate& d, const EventInterface& events){
		delegates_list delegates = eventManager::eventDelegateMap[events.getEventType()];
		//auto findIter = std::find(delegates.begin(),delegates.end(), d);
		int last = 0;
		auto first = delegates.begin();
		while (first != delegates.end()){
			if (*first == d){
				delegates.erase(first);
				break;
			}
			++first;
		}
		if (first == delegates.end() && *first == d){
			delegates.erase(first);
		}
		eventManager::eventDelegateMap[events.getEventType()] = delegates;
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