#ifndef GRIDMAP_CIRCLE
#define GRIDMAP_CIRCLE

#include "mihoyo_macros.h"

class Circle {
 public:
  Circle() : x(0), y(0), radius(0), active(false) {}
  Circle(int x_, int y_, int r_) : x(x_), y(y_), radius(r_), active(true) {}
  bool isActive() { return active; }
  void eliminate() { active = false; }
  int X() const { return x; }
  int Y() const { return y; }
  int Radius() { return radius; }

 private:
  int x;
  int y;
  int radius;
  bool active;
};

#endif /* GRIDMAP_CIRCLE */
