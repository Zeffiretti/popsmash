#include "gridmap/quadtree.h"

#include "gridmap/circle.h"

#include <iostream>
#include <memory>

QuadTree::QuadTree(int level_, Region region_) : level(level_), objects(0), region(region_) {
  children.resize(4);
  for (int i = 0; i < 4; i++) {
    children[i] = nullptr;
  }
}

QuadTree::~QuadTree() {
  children.resize(4);
  for (int i = 0; i < 4; i++) {
    if (children[i] != nullptr) {
      delete children[i];
    }
  }
}

void QuadTree::addCircle(std::shared_ptr<Circle> circle) {
  if (is_leaf) {
    objects++;
    objects_.push_back(circle);
    if (level == kMaxLevels || objects <= kMaxObjects) {
      return;
    }
    split();
    objects_.clear();
    is_leaf = false;
  } else {
    int index = getIndex(circle->X(), circle->Y());
    if (children[index] == nullptr) {
      children[index] = new QuadTree(level + 1, getRegion(index));
    }
    children[index]->addCircle(circle);
  }
}

void QuadTree::split() {
  for (auto circle : objects_) {
    int x = circle->X();
    int y = circle->Y();
    int index = getIndex(x, y);
    if (children[index] == nullptr) {
      children[index] = new QuadTree(level + 1, getRegion(index));
    }
    children[index]->addCircle(circle);
  }
}

void QuadTree::addCircleToMap(int x, int y, int r) {
  std::shared_ptr<Circle> circle = std::make_shared<Circle>(x, y, r);
  addCircle(circle);
}

void QuadTree::clear() {
  objects = 0;
  for (int i = 0; i < 4; i++) {
    if (children[i] != nullptr) {
      children[i]->clear();
    }
  }
}

QuadTree* QuadTree::getChild(int index) { return children[index]; }

std::vector<QuadTree*> QuadTree::getChildren() { return children; }

int QuadTree::getIndex(float x, float y) {
  int index = -1;
  Region child_region = getRegion(0);
  if (x >= child_region.x && x <= child_region.x + child_region.width && y >= child_region.y &&
      y <= child_region.y + child_region.height) {
    index = 0;
  }
  child_region = getRegion(1);
  if (x >= child_region.x && x <= child_region.x + child_region.width && y >= child_region.y &&
      y <= child_region.y + child_region.height) {
    index = 1;
  }
  child_region = getRegion(2);
  if (x >= child_region.x && x <= child_region.x + child_region.width && y >= child_region.y &&
      y <= child_region.y + child_region.height) {
    index = 2;
  }
  child_region = getRegion(3);
  if (x >= child_region.x && x <= child_region.x + child_region.width && y >= child_region.y &&
      y <= child_region.y + child_region.height) {
    index = 3;
  }
  return index;
}

Region QuadTree::getRegion(int index) {
  Region region_;
  switch (index) {
    case 0:
      region_.x = region.x;
      region_.y = region.y;
      region_.width = region.width / 2;
      region_.height = region.height / 2;
      break;
    case 1:
      region_.x = region.x + region.width / 2;
      region_.y = region.y;
      region_.width = region.x + region.width - region_.x;
      region_.height = region.height / 2;
      break;
    case 2:
      region_.x = region.x;
      region_.y = region.y + region.height / 2;
      region_.width = region.width / 2;
      region_.height = region.y + region.height - region_.y;
      break;
    case 3:
      region_.x = region.x + region.width / 2;
      region_.y = region.y + region.height / 2;
      region_.width = region.x + region.width - region_.x;
      region_.height = region.y + region.height - region_.y;
      break;
    default:
      break;
  }
  return region_;
}

bool QuadTree::isVisited() { return visited; }

void QuadTree::setVisited(bool visited) { this->visited = visited; }
