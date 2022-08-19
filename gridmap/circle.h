#ifndef GRIDMAP_CIRCLE
#define GRIDMAP_CIRCLE

#include <iostream>
#include "raylib.h"

class Circle {
 public:
  Circle() : x(0), y(0), radius(0), active(false) {}
  Circle(int x_, int y_, int r_) : x(x_), y(y_), radius(r_), active(true), color(GREEN) {}
  bool isActive() { return active; }
  void eliminate() { active = false; }
  void setColor(Color c) { this->color = c; }
  Color getColor() { return color; }
  int X() const { return x; }
  int Y() const { return y; }
  int Radius() { return radius; }

 private:
  int x;
  int y;
  int radius;
  bool active;
  Color color;
};

#endif /* GRIDMAP_CIRCLE */
