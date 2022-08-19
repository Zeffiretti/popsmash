#ifndef GRIDMAP_CIRCLE
#define GRIDMAP_CIRCLE

class Circle {
 public:
  Circle() : x(0), y(0), radius(0), active(false) {}
  Circle(int x_, int y_, int r_) : x(x_), y(y_), radius(r_), active(true) {}
  bool IsActive() { return active; }
  void Eliminate() { active = false; }
  int GetX() { return x; }
  int GetY() { return y; }
  int GetRadius() { return radius; }

 private:
  int x;
  int y;
  int radius;
  bool active;
};

#endif /* GRIDMAP_CIRCLE */
