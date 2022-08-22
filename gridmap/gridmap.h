#ifndef GRIDMAP_GRIDMAP
#define GRIDMAP_GRIDMAP

#include "gridmap/circle.h"
#include "gridmap/grid.h"
#include "mihoyo_macros.h"

#include <list>
#include <map>
#include <thread>
#include <vector>

class GridMap {
 public:
  GridMap() = default;
  GridMap(int w, int h);
  GridMap(int w, int h, int r);
  ~GridMap();
  void update();
  void logic();
  void render();
  void addCircleToMap(int x, int y);
  void addCircleToMap(int x, int y, int r);
  std::vector<Circle>* getActiveCircles();
  Grid* getGrid(int x, int y) const;
  int getCircleIterator(int key);

 private:
  int width;
  int height;
  int circle_radius;
  int num_circle;
  std::vector<std::vector<Grid*>> grids;
  std::vector<Circle>* active_circles;
  std::map<int, int> circle_indexs;
  int index = 0;

  // parameters for rendering
  const int frame_rate = 60;
  bool button_clicked = true;

  // threads
  std::thread logic_thread;

  void initGrids();
  void initWindow();
};

#endif /* GRIDMAP_GRIDMAP */
