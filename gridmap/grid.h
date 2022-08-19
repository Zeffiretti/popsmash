#ifndef GRIDMAP_GRID
#define GRIDMAP_GRID

#include "gridmap/circle.h"
#include "mihoyo_macros.h"

#include <vector>

class Grid {
 public:
  Grid();
  void addCircle(int circle_index);
  std::vector<int> getCircles() const;

 private:
  std::vector<int> circles;
};

#endif /* GRIDMAP_GRID */
