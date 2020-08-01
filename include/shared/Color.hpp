#pragma once

#include <SDL2/SDL.h>

#include <cmath>
#include <cstdint>
#include <iostream>

struct Color {
  uint32_t m_data;
  Color() = default;
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : m_data{0x00000000} {
    m_data |= r << 24;
    m_data |= g << 16;
    m_data |= b << 8;
    m_data |= a << 0;
  }
  Color(uint32_t color) : m_data{color} {}
  virtual ~Color() { m_data = 0x00000000; }
  uint32_t get() const { return m_data; }
  SDL_Color getSDLColor() const {
    return {.r = static_cast<Uint8>((m_data & 0xff000000) >> 24),
            .g = static_cast<Uint8>((m_data & 0x00ff0000) >> 16),
            .b = static_cast<Uint8>((m_data & 0x0000ff00) >> 8),
            .a = static_cast<Uint8>((m_data & 0x000000ff) >> 0)};
  }
  friend std::ostream& operator<<(std::ostream& ost, const Color& color);
};

Color jetColor(uint8_t n) {
  return {static_cast<uint8_t>(128.0f - 127.0f * cos(n * 0.0123199f * 1.0f)),
          static_cast<uint8_t>(128.0f - 127.0f * cos(n * 0.0123199f * 2.25f)),
          static_cast<uint8_t>(128.0f - 127.0f * cos(n * 0.0123199f * 3.50f)), 0xff};
}

std::ostream& operator<<(std::ostream& ost, const Color& color) {
  ost << "#" << std::hex << color.get();
  return ost;
}
