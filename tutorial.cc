#include <stdio.h>
#include <iostream>

#include "raylib.h"

#include "gridmap/gridmap.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
int main() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test");
  SetTraceLogLevel(LOG_WARNING);
  SetTargetFPS(60);

  GridMap gridmap(WINDOW_WIDTH, WINDOW_HEIGHT);
  // add three circles:
  // 1. (5,5,5)
  // 2. (140,350,100)
  // 3. (350,350,100)
  std::cout << "asfdsfs" << std::endl;
  gridmap.AddCircleToMap(5, 5, 5);
  // std::cout << "asfdsfs" << std::endl;
  // gridmap.AddCircleToMap(140, 350, 100);
  // std::cout << "asfdsfs" << std::endl;
  // gridmap.AddCircleToMap(350, 350, 100);
  // std::cout << "asfdsfs" << std::endl;

  // auto active_circles = gridmap.GetActiveCircles();
  // std::cout << "active_circles.size() = " << active_circles.size() << std::endl;
  // draw the circles on the screen
  while (!WindowShouldClose()) {
    BeginDrawing();
    // std::cout << "num_circle: " << gridmap.GetActiveCircles().size() << std::endl;
    ClearBackground(WHITE);
    // auto c = active_circles.begin();
    // int x = (*c)->GetX();
    // int y = (*c)->GetY();
    // int r = (*c)->GetRadius();
    DrawCircle(100, 100, 50, BLACK);
    EndDrawing();
  }

  CloseWindow();
}