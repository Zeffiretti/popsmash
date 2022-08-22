#include "gridmap/circle.h"
#include "gridmap/grid.h"
#include "gridmap/gridmap.h"
#include "gridmap/line.h"
#include "math/geometry.h"
#include "mihoyo_macros.h"

#include "raylib.h"

#include <random>

const int kWindowWidth = 1000;
const int kWindowHeight = 1000;
// #define WINDOW_HEIGHT 800
int main(int argc, char** argv) {
  GridMap gridmap(kWindowWidth, kWindowHeight, 5);
  // generate 100 random circles with radius 5, x: [0, WINDOW_WIDTH], y: [0, WINDOW_HEIGHT]
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, kWindowWidth - 1);
  const int num_circle = 1000;
  for (int i = 0; i < num_circle; i++) {
    int x = dis(gen);
    int y = dis(gen);
    gridmap.addCircleToMap(x, y, 5);
  }
  gridmap.update();

  CloseWindow();
}