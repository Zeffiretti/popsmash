#ifndef GRIDMAP_LINE
#define GRIDMAP_LINE

// #include "build/_deps/libevent-src/test/regress.h"
#include "mihoyo_macros.h"

#include <cmath>
#include <set>
#include <vector>

class Line {
 public:
  Line() = default;
  Line(int x, int y, int x2, int y2);
  Line(int x, int y, float alpha);
  void calculatePath(int width, int height);
  void calculatePath(int width, int height, int x_margin, int y_margin);
  std::pair<int, int> getStartPoint() const;
  std::vector<int> getEndianPoint() const;
  std::vector<std::pair<float, float>> getPath() const;
  float getAlpha() const;
  void setStartPoint(int x, int y);
  void setAlpha(float alpha);

 private:
  int start_x;
  int start_y;
  int end_x;
  int end_y;
  float alpha;
  std::vector<std::pair<float, float>> path;
  std::set<int> path_set;
};

#endif /* GRIDMAP_LINE */
