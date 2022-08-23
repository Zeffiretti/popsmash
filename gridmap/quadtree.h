#ifndef GRIDMAP_QUADTREE
#define GRIDMAP_QUADTREE

#include "gridmap/circle.h"
#include "gridmap/line.h"
#include "mihoyo_macros.h"

#include <cstddef>
#include <list>
#include <map>
#include <memory>
#include <stack>
#include <vector>

struct Region {
  int x;
  int y;
  int width;
  int height;
  Region(int x_, int y_, int width_, int height_) : x(x_), y(y_), width(width_), height(height_) {}
  Region() : x(0), y(0), width(0), height(0) {}
};

class QuadTree {
 public:
  QuadTree(int level_, Region region_);
  ~QuadTree();
  void addCircle(std::shared_ptr<Circle> circle);
  void addCircleToMap(int x, int y, int r);
  void clear();
  QuadTree* getChild(int index);
  std::vector<QuadTree*> getChildren();
  int getIndex(float x, float y);
  Region getRegion(int index);
  bool isVisited();
  void setVisited(bool visited);
  int getX() const { return region.x; }
  int getY() const { return region.y; }
  int getWidth() const { return region.width; }
  int getHeight() const { return region.height; }
  std::vector<std::shared_ptr<Circle>> getCircles() const { return objects_; }
  bool isLeaf() const { return is_leaf; }
  void split();

 private:
  int level;
  int objects;
  Region region;
  std::vector<std::shared_ptr<Circle>> objects_;
  std::vector<QuadTree*> children;
  bool visited = false;
  bool is_leaf = true;

  const int kMaxObjects = 10;
  const int kMaxLevels = 10;
};
#endif /* GRIDMAP_QUADTREE */
