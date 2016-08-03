/*
  Author:     Charles Shen
  Date:       June 29th, 2016
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

struct Point {
  int x;
  int y;

  Point() {}

  Point(int x, int y): x(x), y(y) {}
};

bool compareXAxis(const Point& v1, const Point& v2) {
  return v1.x < v2.x;
}

bool compareYAxis(const Point& v1, const Point& v2) {
  return v1.y < v2.y;
}

#ifdef DEBUG
void printVectors(const std::vector<Point>& points) {
  for(int i = 0; i < points.size(); ++i) {
    std::cerr << "[" << points[i].x << ", " << points[i].y << "]" << std::endl;
  }
}
#endif

void printVector(const Point& point) {
  std::cout << point.x << " " << point.y << std::endl;
}

void simulateKDTree(std::vector<Point>& sortByX, std::vector<Point>& sortByY, int depth) {
  #ifdef DEBUG
  std::cout << "[Printing sortByX]" << std::endl;
  printVectors(sortByX);
  std::cout << "[Printing sortByY]" << std::endl;
  printVectors(sortByY);
  #endif
  int length = sortByX.size();   // both vectors have the same length

  if (length == 0) // empty set
    return;
  if (length == 1) { // only 1 point, so no need to continue further
    printVector(sortByX[0]);
    return;
  }

  int medianIndex = floor( (length) * 1.0 / 2 );

  std::vector<Point> leftX;
  std::vector<Point> rightX;

  std::vector<Point> leftY;
  std::vector<Point> rightY;

  Point median;
  // Y Axis
  if (depth & 1) {
    median = sortByY[medianIndex];

    // Split at Y
    for (int i = 0; i < length; ++i) {
      if (compareYAxis(sortByY[i], median))
        leftY.push_back(sortByY[i]);
      else if (sortByY[i].y == median.y) {}
      else
        rightY.push_back(sortByY[i]);

      if (compareYAxis(sortByX[i], median))
        leftX.push_back(sortByX[i]);
      else if (sortByX[i].y == median.y) {}
      else
        rightX.push_back(sortByX[i]);
    }
  }
  else { // X Axis
    median = sortByX[medianIndex];

    // Split at X
    for(int i = 0; i < length; ++i) {
      if (compareXAxis(sortByY[i], median))
        leftY.push_back(sortByY[i]);
      else if (sortByY[i].x == median.x) {}
      else
        rightY.push_back(sortByY[i]);

      if (compareXAxis(sortByX[i], median))
        leftX.push_back(sortByX[i]);
      else if (sortByX[i].x == median.x) {}
      else
        rightX.push_back(sortByX[i]);
    }
  }

  printVector(median);

  simulateKDTree(leftX, leftY, depth + 1);
  simulateKDTree(rightX, rightY, depth + 1);
}

int main()
{
  int n;
  std::cin >> n;
  std::vector<Point> sortedByX;
  sortedByX.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x;
    int y;
    std::cin >> x;
    std::cin >> y;
    sortedByX.push_back(Point(x, y));
  }

  std::sort(sortedByX.begin(), sortedByX.end(), compareXAxis);
  std::vector<Point> sortedByY = sortedByX;
  std::sort(sortedByY.begin(), sortedByY.end(), compareYAxis);

  simulateKDTree(sortedByX, sortedByY, 0);
}
