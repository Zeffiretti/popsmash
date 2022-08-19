#include "gridmap/grid.h"

Grid::Grid() { circles.clear(); }

void Grid::AddCircle(Circle circle) { circles.push_back(circle); }