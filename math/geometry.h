#ifndef MATH_GEOMETRY
#define MATH_GEOMETRY

#include "gridmap/circle.h"
#include "gridmap/gridmap.h"
#include "gridmap/line.h"
#include "mihoyo_macros.h"

#include <cmath>
#include <vector>

namespace geometry {

float distance(int x1, int y1, int x2, int y2);

float distance(const Circle& circle, const Line& line);

template <typename T>
float angle(T x1, T y1, T x2, T y2) {
  return atan2(y2 - y1, x2 - x1);
}

}  // namespace geometry

#endif /* MATH_GEOMETRY */
