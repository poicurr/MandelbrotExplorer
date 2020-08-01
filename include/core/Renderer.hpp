#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>

#include <array>
#include <cstdint>
#include <functional>
#include <memory>

#include "../shared/AppConstants.hpp"

struct Renderer {
  std::array<uint32_t, W * H> m_pixels;
  SDL_Renderer* m_renderer;
  SDL_Texture* m_texture;

  explicit Renderer(SDL_Window* window) {
    m_renderer = SDL_CreateRenderer(window, -1, 0);
    m_texture =
        SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, W, H);
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
  }

  ~Renderer() {
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
  }

  using RenderFunc = std::function<void(std::array<uint32_t, W * H>&)>;
  void render(RenderFunc&& renderFunc) { renderFunc(m_pixels); }

  void applyRenderResult() {
    SDL_UpdateTexture(m_texture, nullptr, m_pixels.data(), W * sizeof(uint32_t));
    SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
    SDL_RenderPresent(m_renderer);
  }

  void clear() {
    SDL_RenderClear(m_renderer);
    memset(m_pixels.data(), 0, W * H * sizeof(uint32_t));
  }
};
