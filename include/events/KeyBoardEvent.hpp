#pragma once

#include <SDL2/SDL.h>

#include "./Event.hpp"

struct KeyDownEvent : Event {
  SDL_Keycode code;
  KeyDownEvent(SDL_Keycode code) : code{code} {}
  EVENT_TYPE(EventType::KeyDown);
  EVENT_CATEGORY_MASK(KeyBoard);
};

struct KeyUpEvent : Event {
  SDL_Keycode code;
  KeyUpEvent(SDL_Keycode code) : code{code} {}
  EVENT_TYPE(EventType::KeyUp);
  EVENT_CATEGORY_MASK(KeyBoard);
};
