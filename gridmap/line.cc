#include "gridmap/line.h"

#include "mihoyo_macros.h"

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

void Line::calculatePath(int width, int heigth) {
  float x = start_x;
  float y = start_y;
  float dt = 0.5;
  while (x >= 0 && x < width && y >= 0 && y < heigth) {
    path.push_back(std::make_pair(x, y));
    x += dt * cos(alpha);
    y += dt * sin(alpha);
  }
  end_x = static_cast<int>(x - dt * cos(alpha));
  end_y = static_cast<int>(y - dt * sin(alpha));
}

std::vector<int> Line::getEndPoint() const { return {start_x, start_y, end_x, end_y}; }

std::vector<std::pair<float, float>> Line::getPath() const { return path; }

float Line::getAlpha() const { return alpha; }