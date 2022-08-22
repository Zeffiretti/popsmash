#include "gridmap/gridmap.h"
#include <bits/types/time_t.h>

#include "gridmap/circle.h"
#include "gridmap/grid.h"
#include "gridmap/line.h"
#include "math/geometry.h"
#include "mihoyo_macros.h"
#include "raylib.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

extern Line line;

GridMap::GridMap(int w, int h) : GridMap(w, h, 5) {}

GridMap::GridMap(int w, int h, int r) {
  width = w;
  height = h;
  circle_radius = r;
  active_circles = new std::vector<Circle>();
  initGrids();
  initWindow();
  logic_thread = std::thread(&GridMap::logic, this);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000 / frame_rate));
}

void GridMap::update() {
  while (!WindowShouldClose()) {
    render();
    std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  }
  CloseWindow();
}

void GridMap::logic() {
  while (true) {
    if (line_changed) {
      std::lock_guard<std::mutex> lock(logic_mutex);
      std::vector<std::pair<float, float>> line_path = line.getPath();
      std::cout << "line_path size: " << line_path.size() << std::endl;
      for (std::pair<float, float>& point : line_path) {
        int x = std::roundf(point.first) - x_margin;
        int y = std::roundf(point.second) - y_margin;
        if (x < 0 || x >= width || y < 0 || y >= height) {
          continue;
        }
        if (grids[x][y]->getCircles().empty()) {
          continue;
        }
        std::vector<int> circles = grids[x][y]->getCircles();
        for (int& circle_key : circles) {
          if (((*active_circles)[circle_key].isActive()) &&  // the circle has not been eliminated yet
              geometry::distance((*active_circles)[circle_key], line) < (*active_circles)[circle_key].Radius()) {
            (*active_circles)[circle_key].setColor(RED);
            (*active_circles)[circle_key].eliminate();
          }
        }
      }
      line_changed = false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500 / frame_rate));
  }
}

void GridMap::render() {
  int x = GetMouseX();
  int y = GetMouseY();
  line.setStartPoint(x, y);
  line.calculatePath(width, height, x_margin, y_margin);
  if (!line_changed && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    line_changed = true;
  }
  BeginDrawing();
  ClearBackground(WHITE);
  DrawRectangle(x_margin, y_margin, width, height, BLACK);
  for (auto circle : *active_circles) {
    DrawCircle(circle.X(), circle.Y(), circle.Radius(), circle.getColor());
  }
  auto line_end_points = line.getEndianPoint();
  DrawLine(line_end_points[0], line_end_points[1], line_end_points[2], line_end_points[3], BLACK);
  EndDrawing();
}

void GridMap::addCircleToMap(int x, int y) { addCircleToMap(x, y, circle_radius); }

void GridMap::addCircleToMap(int x, int y, int r) {
  Circle circle = Circle(x + x_margin, y + y_margin, r);
  active_circles->push_back(circle);
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

std::vector<Circle>* GridMap::getActiveCircles() { return active_circles; }

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

void GridMap::initWindow() {
  InitWindow(2 * x_margin + width, 2 * y_margin + height, "PopSmash");
  SetTraceLogLevel(LOG_WARNING);
  SetTargetFPS(frame_rate);
}

void GridMap::initGrids() {
  grids.resize(height);
  for (int y = 0; y < height; y++) {
    grids[y].resize(width);
    for (int x = 0; x < width; x++) {
      grids[y][x] = new Grid();
    }
  }
}

GridMap::~GridMap() = default;
