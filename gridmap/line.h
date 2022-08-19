#ifndef GRIDMAP_LINE
#define GRIDMAP_LINE

#include <cmath>
#include <vector>

class Line {
 public:
  Line(int x, int y, int x2, int y2);
  Line(int x, int y, float alpha);
  void calculatePath(int width, int heigth);
  std::vector<int> getEndPoint() const;
  std::vector<std::pair<float, float>> getPath() const;
  float getAlpha() const;

 private:
  int start_x;
  int start_y;
  int end_x;
  int end_y;
  float alpha;
  std::vector<std::pair<float, float>> path;
};

#endif /* GRIDMAP_LINE */
