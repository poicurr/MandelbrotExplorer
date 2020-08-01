#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdlib.h>

#include <cmath>
#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "../components/ColorBar.hpp"
#include "../components/Mandelbrot.hpp"
#include "../events/EventDispatcher.hpp"
#include "./Renderer.hpp"

static bool quitting = false;

class Window {
  SDL_Window* m_window;
  std::unique_ptr<Renderer> m_renderer;

 public:
  Window() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    }
    m_window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                W * PIXEL_SIZE, H * PIXEL_SIZE, SDL_WINDOW_RESIZABLE);
    m_renderer = std::make_unique<Renderer>(m_window);
    SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    SDL_SetCursor(cursor);
  }

  ~Window() {
    m_renderer.reset();
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    quitting = false;
  }

  void start() {
    int t1 = 0, t2 = 0, elapsedTime = 0;

    // ---------------------------------------------
    // create components
    // ---------------------------------------------
    Mandelbrot demo;
    ColorBar bar;

    while (!quitting) {
      if (!t1) {
        t1 = SDL_GetTicks();
      } else {
        elapsedTime = t2 - t1;
      }

      m_renderer->clear();

      // ---------------------------------------------
      // event loop
      // ---------------------------------------------
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        std::unique_ptr<Event> ev = EventDispatcher::dispatch(event);
        demo.dispatch(ev.get());
        if (event.type == SDL_QUIT) {
          quitting = true;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
          quitting = true;
        }
      }

      // ---------------------------------------------
      // update pixel data
      // ---------------------------------------------
      m_renderer->render([&](std::array<uint32_t, W * H>& pixels) {
        demo.render(pixels);
        bar.render(pixels);
      });
      m_renderer->applyRenderResult();

      // render fps counter
      if (elapsedTime < 32) {
        SDL_Delay(32 - elapsedTime);
      }
      // int fps = 1000 / (SDL_GetTicks() - t1);
      t1 = t2;
      t2 = SDL_GetTicks();
    }
  }
};
