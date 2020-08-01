#pragma once

#include <functional>
#include <unordered_map>

#include "./Event.hpp"

using EventHandlerType = std::function<void(Event*)>;

class EventHandler {
  std::unordered_map<EventType, EventHandlerType> m_handlers;

 public:
  void addEventHandler(EventType type, EventHandlerType handler) { m_handlers[type] = handler; }
  void dispatch(Event* ev) {
    if (!ev) return;
    if (m_handlers.find(ev->type()) == m_handlers.end()) return;
    auto handler = m_handlers[ev->type()];
    handler(ev);
  }
};
