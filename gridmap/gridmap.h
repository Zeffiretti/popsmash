#ifndef GRIDMAP_GRIDMAP
#define GRIDMAP_GRIDMAP

#include "gridmap/circle.h"
#include "gridmap/line.h"
#include "gridmap/quadtree.h"
#include "mihoyo_macros.h"

#include <time.h>
#include <list>
#include <map>
#include <memory>
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
  //int getCircleIterator(int key);
  void collisionDetection();

 private:
  int width;
  int height;
  int x_margin = 100;
  int y_margin = 100;
  int circle_radius;
  std::vector<std::shared_ptr<Circle>> active_circles;
  Line line;
  QuadTree* quad_tree_root;

  // parameters for rendering
  const int frame_rate = 50;
  bool line_changed = false;
  bool mouse_clicked = false;

  // threads
  std::thread logic_thread;
  std::mutex logic_mutex;
  bool terminate = false;

  void initWindow();
};

#endif /* GRIDMAP_GRIDMAP */
