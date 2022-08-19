#include "gridmap/gridmap.h"
#include <list>
#include "gridmap/circle.h"

GridMap::GridMap(int w, int h) {
  width = w;
  height = h;
  grids = std::vector<std::vector<Grid*>>(w, std::vector<Grid*>(h));
}

GridMap::GridMap(int w, int h, int r) {
  width = w;
  height = h;
  circle_radius = r;
  grids = std::vector<std::vector<Grid*>>(w, std::vector<Grid*>(h));
}

void GridMap::AddCircleToMap(int x, int y) { AddCircleToMap(x, y, circle_radius); }

void GridMap::AddCircleToMap(int x, int y, int r) {
  Circle circle = Circle(x, y, r);
  active_circles.push_back(circle);
  // // int index = x + y * width;
  // // circle_indexs[index] = active_circles.end();
  // // link the grids the circle covers to the circle
  for (int i = x - r; i <= x + r; i++) {
    for (int j = y - r; j <= y + r; j++) {
      if (i >= 0 && i < width && j >= 0 && j < height) {
        grids[i][j]->AddCircle(circle);
      }
    }
  }
}

std::list<Circle> GridMap::GetActiveCircles() const { return active_circles; }