#include "gridmap/gridmap.h"
#include "mihoyo_macros.h"

#include <random>

const int kWindowWidth = 1000;
const int kWindowHeight = 1000;

// argv:
// 1: number of random circles
// 2: circle distribution type [uniform, normal, exponential]
// if 2 is uniform, 3 is the lower bound, 4 is the upper bound. Since the map is
//    1200x1200, the lower bound should be at least 100, and the upper bound
//    should be at most 1100.
// if 2 is normal, 3 is the mean, 4 is the standard deviation. The recommanded mean
//    is 600.
// if 2 is exponential, 3 is the lambda
int main(int argc, char** argv) {
  GridMap gridmap(kWindowWidth, kWindowHeight, 5);
  // get the specific random number distribution
  int num_circle = 3000;
  std::string dist_type = "uniform";
  int dist_arg1 = 100;
  int dist_arg2 = 1100;
  if (argc > 1) {
    num_circle = atoi(argv[1]);
    dist_type = argv[2];
    if (dist_type == "uniform") {
      dist_arg1 = atoi(argv[3]);
      dist_arg2 = atoi(argv[4]);
    } else if (dist_type == "normal") {
      dist_arg1 = atoi(argv[3]);
      dist_arg2 = atoi(argv[4]);
    } else if (dist_type == "exponential") {
      dist_arg1 = atoi(argv[3]);
    }
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> udis(dist_arg1, dist_arg2);
  std::normal_distribution<> ndis(dist_arg1, dist_arg2);
  std::exponential_distribution<> edis(dist_arg1);

  for (int i = 0; i < num_circle; i++) {
    int x = 100, y = 100;
    if (dist_type == "uniform") {
      x = udis(gen);
      y = udis(gen);
    } else if (dist_type == "normal") {
      x = ndis(gen);
      y = ndis(gen);
    } else if (dist_type == "exponential") {
      x = edis(gen);
      y = edis(gen);
    }
    if (x < 100 || x > 1100 || y < 100 || y > 1100) {  // the circle will not be displayed
      continue;
    }
    gridmap.addCircleToMap(x, y, 5);
  }
  gridmap.update();
}