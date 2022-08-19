#include "math/geometry.h"
#include <math.h>
#include <vector>

namespace geometry {

float distance(int x1, int y1, int x2, int y2) { return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); }

float distance(const Circle& circle, const Line& line) {
  std::vector<int> path = line.getEndPoint();
  float alpha = line.getAlpha();
  // line: y = ax + b
  float a = tan(alpha);
  float b = path[1] - a * path[0];
  // circle: (x - xc)^2 + (y - yc)^2 = r^2
  float xc = circle.X();
  float yc = circle.Y();

  // calculate the distance between the line and the circle center
  float d = fabs(a * xc + b - yc) / sqrt(a * a + 1);
  return d;
}

}  // namespace geometry