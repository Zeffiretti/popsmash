#ifndef MATH_GEOMETRY
#define MATH_GEOMETRY

#include <cmath>
#include <vector>

#include "gridmap/circle.h"
#include "gridmap/gridmap.h"
#include "gridmap/line.h"

namespace geometry {

float distance(int x1, int y1, int x2, int y2);

float distance(const Circle& circle, const Line& line);

}  // namespace geometry

#endif /* MATH_GEOMETRY */