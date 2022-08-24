#include "gridmap/gridmap.h"
#include <exception>
#include <memory>

#include "gridmap/circle.h"
#include "gridmap/quadtree.h"
#include "math/geometry.h"
#include "mihoyo_macros.h"
namespace raylib {
#include "raylib.h"
}

#include <chrono>
#include <cmath>
#include <iostream>
#include <list>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

GridMap::GridMap(int w, int h) : GridMap(w, h, 5) {}

GridMap::GridMap(int w, int h, int r) {
  width = w;
  height = h;
  circle_radius = r;
  active_circles.clear();
  quad_tree_root = new QuadTree(0, Region(x_margin, y_margin, width, height));
  initWindow();
  logic_thread = std::thread(&GridMap::logic, this);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000 / frame_rate));
}

void GridMap::update() {
  while (!raylib::WindowShouldClose()) {
    render();
  }
  terminate = true;
  // terminate logic thread
  logic_thread.join();
  raylib::MCloseWindow();
}

void GridMap::logic() {
  while (!terminate) {
    if (line_changed) {
      std::lock_guard<std::mutex> lock(logic_mutex);
      collisionDetection();
      line_changed = false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500 / frame_rate));
  }
}

void GridMap::render() {
  int x = raylib::GetMouseX();
  int y = raylib::GetMouseY();
  if (mouse_clicked) {
    std::pair<int, int> point = line.getStartPoint();
    double alpha = geometry::angle(point.first, point.second, x, y);
    line.setAlpha(alpha);
    line.calculatePath(width, height, x_margin, y_margin);
    if (!line_changed && raylib::IsMouseButtonPressed(raylib::MOUSE_LEFT_BUTTON)) {
      line_changed = true;
      mouse_clicked = false;
    }
  } else {
    if (raylib::IsMouseButtonPressed(raylib::MOUSE_LEFT_BUTTON)) {
      mouse_clicked = true;
      line.setStartPoint(x, y);
    }
  }
  raylib::BeginDrawing();
  raylib::ClearBackground(raylib::WHITE);
  raylib::DrawRectangle(x_margin, y_margin, width, height, raylib::BLACK);
  for (auto circle : active_circles) {
    raylib::Color color = circle->isActive() ? raylib::GREEN : raylib::RED;
    raylib::DrawCircle(circle->X(), circle->Y(), circle->Radius(), color);
  }
  auto line_end_points = line.getEndianPoint();
  if (mouse_clicked) {
    raylib::DrawLine(line_end_points[0], line_end_points[1], line_end_points[2], line_end_points[3], raylib::YELLOW);
  }
  raylib::DrawCircle(x, y, 5, raylib::BLACK);

  raylib::EndDrawing();
}

void GridMap::addCircleToMap(int x, int y) { addCircleToMap(x, y, circle_radius); }

void GridMap::addCircleToMap(int x, int y, int r) {
  std::shared_ptr<Circle> circle = std::make_shared<Circle>(x, y, r);
  quad_tree_root->addCircle(circle);
  active_circles.push_back(circle);
}

void GridMap::initWindow() {
  raylib::InitWindow(2 * x_margin + width, 2 * y_margin + height, "PopSmash");
  raylib::SetTraceLogLevel(raylib::LOG_WARNING);
  raylib::SetTargetFPS(frame_rate);
}

void GridMap::collisionDetection() {
  std::queue<QuadTree*> visited_nodes;
  line.calculatePath(width, height, x_margin, y_margin);
  std::vector<std::pair<float, float>> line_path = line.getPath();
  for (std::pair<float, float>& point : line_path) {
    QuadTree* root = quad_tree_root;
    float x = point.first;
    float y = point.second;
    if (x < x_margin || x > x_margin + width || y < y_margin || y > y_margin + height) {
      continue;
    }
    while (root != nullptr && !root->isLeaf()) {
      int index = root->getIndex(x, y);
      root = root->getChild(index);
    }
    if (root == nullptr) {
      continue;
    }
    if (root->isVisited()) {
      continue;
    }
    for (int i = 0; i < root->getCircles().size(); i++) {
      auto circle = root->getCircles().at(i);
      if (circle->isActive() && geometry::distance(*circle, line) <= circle->Radius()) {
        circle->eliminate();
      }
    }
    root->setVisited(true);
    visited_nodes.push(root);
  }
  while (!visited_nodes.empty()) {
    QuadTree* node = visited_nodes.front();
    visited_nodes.pop();
    node->setVisited(false);
  }
}

GridMap::~GridMap() = default;
