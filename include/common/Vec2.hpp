#pragma once

#include <cmath>
#include <concepts>

template <typename T>
concept Number = requires(T a, T b) {
  a + b;
  a - b;
  a* b;
  a / b;
};

template <Number T>
struct Vec2 {
  using type = T;
  T x, y;

  Vec2() : x{0}, y{0} {}
  Vec2(const T& x, const T& y) : x{x}, y{y} {}
  Vec2(const Vec2<T>& other) : x{other.x}, y{other.y} {}
  Vec2& operator=(const Vec2<T>& other) {
    x = other.x;
    y = other.y;
    return *this;
  }

  Vec2 operator-(const Vec2<T>& other) const { return {x - other.x, y - other.y}; }
  Vec2 operator+(const Vec2<T>& other) const { return {x + other.x, y + other.y}; }
  Vec2 operator-(int n) const { return {x - n, y - n}; }
  Vec2 operator+(int n) const { return {x + n, y + n}; }

  T length() { return std::sqrt(x * x + y * y); }

  void normalize() {
    T length = length();
    x /= length;
    y /= length;
  }

  Vec2<T> rotate(const Vec2<T>& center, float angle) const {
    T rx = x - center.x, ry = y - center.y;
    return {rx * cosf(angle) + ry * sinf(angle) + center.x,
            -rx * sinf(angle) + ry * cosf(angle) + center.y};
  }
};
