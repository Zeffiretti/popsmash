#ifndef GRIDMAP_GRIDMAP
#define GRIDMAP_GRIDMAP

// #include "raylib.h"

#include "gridmap/circle.h"
#include "gridmap/grid.h"

#include <list>
#include <map>
#include <vector>

class GridMap {
 public:
  GridMap() = default;
  GridMap(int w, int h);
  GridMap(int w, int h, int r);
  void AddCircleToMap(int x, int y);
  void AddCircleToMap(int x, int y, int r);
  std::list<Circle> GetActiveCircles() const;

 private:
  int width;
  int height;
  int circle_radius;
  int num_circle;
  std::vector<std::vector<Grid*>> grids;
  std::list<Circle> active_circles;
  std::map<int, std::list<Circle*>::iterator> circle_indexs;
};

#endif /* GRIDMAP_GRIDMAP */
