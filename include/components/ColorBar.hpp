#pragma once

#include "./Component.hpp"

struct ColorBar : Component {
  virtual void render(std::array<uint32_t, W * H>& pixels) override {
    for (int i = 0; i < 256; ++i) {
      const uint32_t color = jetColor(i).get();
      pixels[i + W - 256 + W * (H - 1)] = color;
      pixels[i + W - 256 + W * (H - 2)] = color;
      pixels[i + W - 256 + W * (H - 3)] = color;
      pixels[i + W - 256 + W * (H - 4)] = color;
    }
  }
};
