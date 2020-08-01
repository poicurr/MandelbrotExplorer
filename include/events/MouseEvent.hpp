#pragma once

#include <SDL2/SDL.h>

#include "../common/Vec2.hpp"
#include "../core/MouseCodes.hpp"
#include "../shared/Mouse.hpp"
#include "Event.hpp"

struct MouseMoveEvent : public Event {
  Vec2<int> prev, curr;
  MouseMoveEvent() {}
  MouseMoveEvent(int x, int y) {
    prev.x = Mouse::X;
    prev.y = Mouse::Y;
    curr.x = x;
    curr.y = y;
    Mouse::X = x;
    Mouse::Y = y;
  }
  EVENT_TYPE(EventType::MouseMove);
  EVENT_CATEGORY_MASK(Mouse);
};

struct MouseDownEvent : public Event {
  MouseCodes code;
  MouseDownEvent() : code{MouseCodes::None} {}
  MouseDownEvent(const MouseCodes& code) : code{code} { Mouse::isHeld = true; }
  EVENT_TYPE(EventType::MouseDown);
  EVENT_CATEGORY_MASK(Mouse);
};

struct MouseUpEvent : public Event {
  MouseCodes code;
  MouseUpEvent() : code{MouseCodes::None} {}
  MouseUpEvent(const MouseCodes& code) : code{code} { Mouse::isHeld = false; }
  EVENT_TYPE(EventType::MouseUp);
  EVENT_CATEGORY_MASK(Mouse);
};

struct MouseWheelEvent : public Event {
  int y;
  MouseWheelEvent(int y) : y{y} {}
  EVENT_TYPE(EventType::MouseWheel);
  EVENT_CATEGORY_MASK(Mouse);
};
