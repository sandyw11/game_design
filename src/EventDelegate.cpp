#include "EventDelegate.hpp"

EventDelegate::EventDelegate(){

}
EventDelegate::EventDelegate(std::function<void(const EventInterface&)> input,int ID){
	this->delegateId = ID;
	this->callback = input;
}