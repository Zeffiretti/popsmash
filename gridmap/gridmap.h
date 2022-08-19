#ifndef GRIDMAP_GRIDMAP
#define GRIDMAP_GRIDMAP

#include "gridmap/circle.h"
#include "gridmap/grid.h"
#include "mihoyo_macros.h"

#include <list>
#include <map>
#include <vector>

class GridMap {
 public:
  GridMap() = default;
  GridMap(int w, int h);
  GridMap(int w, int h, int r);
  void addCircleToMap(int x, int y);
  void addCircleToMap(int x, int y, int r);
  std::vector<Circle> getActiveCircles() const;
  Grid* getGrid(int x, int y) const;
  int getCircleIterator(int key);

 private:
  int width;
  int height;
  int circle_radius;
  int num_circle;
  std::vector<std::vector<Grid*>> grids;
  std::vector<Circle> active_circles;
  std::map<int, int> circle_indexs;
  int index = 0;

  void InitGrids();
};

#endif /* GRIDMAP_GRIDMAP */
