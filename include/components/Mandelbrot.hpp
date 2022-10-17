#pragma once

#include <array>
#include <complex>

#include "../common/Vec2.hpp"
#include "../common/thread.hpp"
#include "../shared/Color.hpp"
#include "./Component.hpp"

struct Mandelbrot : Component {
  Vec2<double> offset;
  Vec2<double> scale;
  Vec2<double> worldTopLeft, worldBottomRight;
  int maxIteration = 64;
  ThreadPool pool;

  Mandelbrot()
      : offset{-2.2, -1.0},
        scale{static_cast<double>(W / 3.0), static_cast<double>(H / 2.0)},
        worldTopLeft{screenToWorld({0, 0})},
        worldBottomRight{screenToWorld({W, H})},
        pool{8} {
    this->addEventListener(EventType::MouseMove, [this](Event* ev) {
      auto mouseMove = static_cast<MouseMoveEvent*>(ev);
      if (Mouse::isHeld) {
        // drag
        const auto prev = screenToWorld(mouseMove->prev);
        const auto curr = screenToWorld(mouseMove->curr);
        const auto amount = curr - prev;
        offset.x -= amount.x / PIXEL_SIZE;
        offset.y -= amount.y / PIXEL_SIZE;
      }
    });

    this->addEventListener(EventType::MouseWheel, [this](Event* ev) {
      auto mouseWheel = static_cast<MouseWheelEvent*>(ev);
      if (mouseWheel->y > 0) {
        // zoom in
        zoom(1.1);
      } else {
        // zoom out
        zoom(0.9);
      }
    });

    this->addEventListener(EventType::KeyDown, [this](Event* ev) {
      auto keydown = static_cast<KeyDownEvent*>(ev);
      if (keydown->code == SDLK_UP) {
        maxIteration += 16;
        std::cout << "[info] maxIteration: " << maxIteration << std::endl;
      }
      if (keydown->code == SDLK_DOWN) {
        if (maxIteration <= 16) return;
        maxIteration -= 16;
        std::cout << "[info] maxIteration: " << maxIteration << std::endl;
      }
    });
  }

  void zoom(double rate) {
    auto p1 = screenToWorld({Mouse::X / PIXEL_SIZE, Mouse::Y / PIXEL_SIZE});
    scale.x *= rate;
    scale.y *= rate;
    auto p2 = screenToWorld({Mouse::X / PIXEL_SIZE, Mouse::Y / PIXEL_SIZE});
    offset.x += p1.x - p2.x;
    offset.y += p1.y - p2.y;
  }

  Vec2<double> screenToWorld(const Vec2<int>& screen) {
    return {(double)screen.x / scale.x + offset.x,
            (double)screen.y / scale.y + offset.y};
  }

  virtual void render(std::array<uint32_t, W * H>& pixels) override {
    auto renderRegion = [&](int x1, int x2) {
      for (int y = 0; y < H; ++y) {
        for (int x = x1; x < x2; ++x) {
          const auto world = screenToWorld({x, y});
          auto zr = double{0.0}, zi = double{0.0};
          auto cr = world.x, ci = world.y;
          int iter = 0;
          while (zr * zr + zi * zi < 4.0 && iter < maxIteration) {
            const double zr2 = zr * zr, zi2 = zi * zi, zri = zr * zi;
            zr = zr2 - zi2 + cr;
            zi = zri + zri + ci;
            iter++;
          }
          if (iter == maxIteration) {
            // 収束したと判断 → 黒く塗りつぶす
            pixels[x + W * y] = 0;
          } else {
            // 収束しなかった場合は発散する速さをもとに着色
            const Color color = jetColor(iter);
            pixels[x + W * y] = color.get();
          }
        }
      }
    };

    int w = W / 8;
    std::array<std::future<void>, 8> futures;
    for (int i = 0; i < 8; ++i) {
      futures[i] = pool.enqueue(renderRegion, w * i, w * i + w);
    }
    for (int i = 0; i < 8; ++i) futures[i].get();
  }
};
