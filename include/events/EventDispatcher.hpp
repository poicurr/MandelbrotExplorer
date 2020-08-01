#pragma once

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>

#include "../events/Event.hpp"
#include "../events/KeyBoardEvent.hpp"
#include "../events/MouseEvent.hpp"

struct EventDispatcher {
  static std::unique_ptr<Event> dispatch(const SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION) {
      return std::make_unique<MouseMoveEvent>(event.motion.x, event.motion.y);
    }
    if (event.type == SDL_MOUSEWHEEL) {
      return std::make_unique<MouseWheelEvent>(event.wheel.y);
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
      if (event.button.button == SDL_BUTTON_LEFT)
        return std::make_unique<MouseDownEvent>(MouseCodes::Left);
      if (event.button.button == SDL_BUTTON_MIDDLE)
        return std::make_unique<MouseDownEvent>(MouseCodes::Middle);
      if (event.button.button == SDL_BUTTON_RIGHT)
        return std::make_unique<MouseDownEvent>(MouseCodes::Right);
    }
    if (event.type == SDL_MOUSEBUTTONUP) {
      if (event.button.button == SDL_BUTTON_LEFT)
        return std::make_unique<MouseUpEvent>(MouseCodes::Left);
      if (event.button.button == SDL_BUTTON_MIDDLE)
        return std::make_unique<MouseUpEvent>(MouseCodes::Middle);
      if (event.button.button == SDL_BUTTON_RIGHT)
        return std::make_unique<MouseUpEvent>(MouseCodes::Right);
    }
    if (event.type == SDL_KEYDOWN) {
      return std::make_unique<KeyDownEvent>(event.key.keysym.sym);
    }
    return nullptr;
  }
};
