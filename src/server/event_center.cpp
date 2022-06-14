#include "event_center.h"

EventCenter::EventCenter() {
    m_event_base = event_base_new();
}

EventCenter::~EventCenter() {
    event_base_free(m_event_base);
    m_event_base = nullptr;
}
