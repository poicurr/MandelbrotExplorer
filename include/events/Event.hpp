#pragma once

#include <cstdint>

enum class EventType { None = 0, KeyDown, KeyUp, MouseMove, MouseDown, MouseUp, MouseWheel };

#define BIT(n) 1 << n
enum EventCategory { None = 0, KeyBoard = BIT(1), Mouse = BIT(2) };
#undef BIT

#define EVENT_TYPE(eventType)                             \
  virtual EventType type() override { return eventType; } \
  virtual const char* name() override { return #eventType; }

#define EVENT_CATEGORY_MASK(eventCategory) \
  virtual int categoryMask() override { return eventCategory; }

struct Event {
  virtual ~Event() = default;
  virtual EventType type() = 0;
  virtual const char* name() = 0;
  virtual int categoryMask() = 0;
  bool isInCategory(EventCategory category) { return categoryMask() & category; }
};
