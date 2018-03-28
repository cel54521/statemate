/**
 * @file event.h
 * @brief event
 * @author cel54521
 */
#ifndef _EVENT_
#define _EVENT_

#include <vector>

typedef struct _Event {
    char eventName[10240];
    char condition[10240];
} Event;

class EventList {
private:
    std::vector<Event*> eventList;
public:
    EventList(void);
    ~EventList(void);

    Event* newEvent(void);
    void print(void);

};

#endif
