#pragma once

#include <event2/event.h>

class EventCenter {
public:
    EventCenter();
    ~EventCenter();
private:
    struct event_base *m_event_base{nullptr};
};


