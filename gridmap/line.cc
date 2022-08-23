#include "gridmap/line.h"

#include "mihoyo_macros.h"

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

Line::Line(int x, int y, int x2, int y2) {
  start_x = x;
  start_y = y;
  alpha = atan2(y2 - y, x2 - x);
}

Line::Line(int x, int y, float alpha) {
  start_x = x;
  start_y = y;
  // convert alpha to [-pi, pi]
  while (alpha > M_PI) {
    alpha -= 2 * M_PI;
  }
  while (alpha < -M_PI) {
    alpha += 2 * M_PI;
  }
  this->alpha = alpha;
}

void Line::calculatePath(int width, int height) { calculatePath(width, height, 0, 0); }

void Line::calculatePath(int width, int height, int x_margin, int y_margin) {
  path_set.clear();
  path.clear();
  float x = start_x;
  float y = start_y;
  float dt = 1.0;
  while (x >= 0 && x < width + 2 * x_margin && y >= 0 && y < height + 2 * y_margin) {
    int ix = std::round(x);
    int iy = std::round(y);
    int idx = ix + iy * 1000;
    if (path_set.find(idx) == path_set.end()) {
      path_set.insert(idx);
      path.push_back(std::make_pair(x, y));
    }
    x += dt * cos(alpha);
    y += dt * sin(alpha);
  }
  end_x = static_cast<int>(x - dt * cos(alpha));
  end_y = static_cast<int>(y - dt * sin(alpha));
}

std::pair<int, int> Line::getStartPoint() const { return std::make_pair(start_x, start_y); }

std::vector<int> Line::getEndianPoint() const { return {start_x, start_y, end_x, end_y}; }

std::vector<std::pair<float, float>> Line::getPath() const { return path; }

float Line::getAlpha() const { return alpha; }

void Line::setStartPoint(int x, int y) {
  start_x = x;
  start_y = y;
}

void Line::setAlpha(float alpha) { this->alpha = alpha; }