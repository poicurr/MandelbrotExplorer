#pragma once

#include <array>
#include <initializer_list>
#include <unordered_map>
#include <vector>

#include "../events/Event.hpp"
#include "../shared/AppConstants.hpp"
#include "../events/EventHandler.hpp"
#include "../events/MouseEvent.hpp"
#include "../events/KeyBoardEvent.hpp"

struct Component {
  EventHandler m_handler;
  void addEventListener(EventType type, EventHandlerType &&handler) {
    m_handler.addEventHandler(type, handler);
  }
  void dispatch(Event *ev) { m_handler.dispatch(ev); }
  virtual void render(std::array<uint32_t, W * H> &pixels) = 0;
};
