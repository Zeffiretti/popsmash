#ifndef GRIDMAP_GRID
#define GRIDMAP_GRID

#include "gridmap/circle.h"

#include <vector>

class Grid {
 public:
  Grid();
  void AddCircle(Circle circle);

 private:
  std::vector<Circle> circles;
};

#endif /* GRIDMAP_GRID */
