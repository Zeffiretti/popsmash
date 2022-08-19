#include "gridmap/grid.h"
#include "mihoyo_macros.h"

#include <vector>

Grid::Grid() { circles.clear(); }

void Grid::addCircle(int circle_index) { circles.push_back(circle_index); }

std::vector<int> Grid::getCircles() const { return circles; }