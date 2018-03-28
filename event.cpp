/**
 * @file event.cpp
 * @brief event
 * @author cel54521
 */
#include "event.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EventList::EventList(void) {

}

EventList::~EventList(void) {
    std::vector<Event*>::iterator itr;

    for (itr = eventList.begin(); itr < eventList.end(); itr++) {
        free(*itr);
    }
}

Event* EventList::newEvent() {
    Event *tmp = (Event*) malloc(sizeof(Event));

    strcpy(tmp->eventName, "");
    strcpy(tmp->condition, "");
    this->eventList.push_back(tmp);

    return tmp;
}

void EventList::print(void) {
    std::vector<Event*>::iterator itr;

    fprintf(stderr, "Event\n");
    for (itr = eventList.begin(); itr < eventList.end(); itr++) {
        fprintf(stderr, "%s,%s\n", (*itr)->eventName, (*itr)->condition);
    }
}
