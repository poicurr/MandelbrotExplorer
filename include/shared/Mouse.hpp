#pragma once

struct Mouse {
  static int X, Y;
  static bool isHeld;
};

bool Mouse::isHeld = false;

int Mouse::X = 0;
int Mouse::Y = 0;
