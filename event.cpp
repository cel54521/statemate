/**
 * @file event.cpp
 * @brief event
 * @author cel54521
 */
#include "event.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EventList::EventList(void){

}

EventList::~EventList(void){
  std::vector<Event*>::iterator itr;

  for(itr = eventList.begin(); itr < eventList.end(); itr++){
    free(*itr);
  }
}

void EventList::push(Event event){
  Event *tmp = (Event*)malloc(sizeof(Event));

  strcpy(tmp->eventName, event.eventName);
  strcpy(tmp->condition, event.condition);
  this->eventList.push_back(tmp);
}

void EventList::print(void){
  std::vector<Event*>::iterator itr;

  for(itr = eventList.begin(); itr < eventList.end(); itr++){
    fprintf(stderr, "%s,%s\n", (*itr)->eventName, (*itr)->condition);
  }
}
