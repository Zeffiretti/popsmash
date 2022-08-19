#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

#include "gridmap/circle.h"
#include "raylib.h"

#include "gridmap/grid.h"
#include "gridmap/gridmap.h"
#include "gridmap/line.h"
#include "math/geometry.h"
#include "mihoyo_macros.h"

const int kWindowWidth = 1000;
const int kWindowHeight = 1000;
// #define WINDOW_HEIGHT 800
int main(int argc, char** argv) {
  InitWindow(kWindowWidth, kWindowHeight, "Test");
  SetTraceLogLevel(LOG_WARNING);
  const int frame_rate = 60;
  SetTargetFPS(frame_rate);

  GridMap gridmap(kWindowWidth, kWindowHeight, 5);
  // generate 100 random circles with radius 5, x: [0, WINDOW_WIDTH], y: [0, WINDOW_HEIGHT]
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, kWindowWidth - 1);
  const int num_circle = 1000;
  for (int i = 0; i < num_circle; i++) {
    int x = dis(gen);
    int y = dis(gen);
    gridmap.addCircleToMap(x, y, 10);
  }
  std::vector<Circle> active_circles = gridmap.getActiveCircles();

  // read input parameters
  int line_x = 400;
  int line_y = 700;
  float line_alpha = -M_PI_4;
  if (argc == 4) {
    line_x = atoi(argv[1]);
    line_y = atoi(argv[2]);
    line_alpha = atof(argv[3]);
  }
  Line line(line_x, line_y, line_alpha);
  line.calculatePath(kWindowWidth, kWindowHeight);
  auto line_end_points = line.getEndPoint();
  auto line_path = line.getPath();
  for (auto& point : line_path) {
    int x = std::round(point.first);
    int y = std::round(point.second);
    Grid* grid = gridmap.getGrid(x, y);
    if (grid == nullptr || grid->getCircles().empty()) {
      continue;
    }
    auto circles = grid->getCircles();

    for (auto& circle_key : circles) {
      // active_circles[circle_key].setColor(RED);
      auto circle = active_circles[circle_key];
      if (geometry::distance(circle, line) < circle.Radius()) {
        circle.setColor(RED);
        active_circles[circle_key] = circle;
      }
    }
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    for (auto circle : active_circles) {
      if (circle.isActive()) {
        DrawCircle(circle.X(), circle.Y(), circle.Radius(), circle.getColor());
      }
    }
    // draw a line with the mouse position
    // DrawLine(GetMouseX(), GetMouseY(), GetMouseX() + 100, GetMouseY() + 100, BLACK);
    DrawLine(line_end_points[0], line_end_points[1], line_end_points[2], line_end_points[3], BLACK);
    EndDrawing();
  }

  CloseWindow();
}