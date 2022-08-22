#ifndef GRIDMAP_GRIDMAP
#define GRIDMAP_GRIDMAP

#include "gridmap/circle.h"
#include "gridmap/grid.h"
#include "gridmap/line.h"
#include "mihoyo_macros.h"

#include <bits/types/time_t.h>
#include <time.h>
#include <list>
#include <map>
#include <mutex>
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
  int x_margin = 100;
  int y_margin = 100;
  int circle_radius;
  int num_circle;
  std::vector<std::vector<Grid*>> grids;
  std::vector<Circle>* active_circles;
  Line line;
  std::map<int, int> circle_indexs;
  int index = 0;

  // parameters for rendering
  const int frame_rate = 50;
  bool line_changed = false;
  bool mouse_clicked = false;

  // threads
  std::thread logic_thread;
  std::mutex logic_mutex;

  void initGrids();
  void initWindow();
};

#endif /* GRIDMAP_GRIDMAP */
