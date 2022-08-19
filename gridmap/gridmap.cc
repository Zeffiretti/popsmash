#include "gridmap/gridmap.h"
#include "gridmap/circle.h"

#include <cmath>
#include <iostream>
#include <list>

GridMap::GridMap(int w, int h) {
  width = w;
  height = h;
  circle_radius = 5;
  InitGrids();
}

GridMap::GridMap(int w, int h, int r) {
  width = w;
  height = h;
  circle_radius = r;
  InitGrids();
}

void GridMap::addCircleToMap(int x, int y) { addCircleToMap(x, y, circle_radius); }

void GridMap::addCircleToMap(int x, int y, int r) {
  Circle circle = Circle(x, y, r);
  active_circles.push_back(circle);
  // link the grids the circle covers to the circle
  for (int i = std::max(0, x - r); i <= std::min(height - 1, x + r); i++) {
    for (int j = std::max(0, y - r); j <= std::min(width - 1, y + r); j++) {
      if (i >= 0 && i < height && j >= 0 && j < width) {
        grids[i][j]->addCircle(index);
      }
    }
  }
  index++;
}

std::vector<Circle> GridMap::getActiveCircles() const { return active_circles; }

void GridMap::InitGrids() {
  grids.resize(height);
  for (int y = 0; y < height; y++) {
    grids[y].resize(width);
    for (int x = 0; x < width; x++) {
      grids[y][x] = new Grid();
    }
  }
}

Grid* GridMap::getGrid(int x, int y) const {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    return nullptr;
  }
  return grids[x][y];
}

int GridMap::getCircleIterator(int key) {
  // if (circle_indexs.find(key) == circle_indexs.end()) {
  //   return active_circles.end();
  // }
  return 0;
}