#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::vector;

// The algorithm is very simple, but first we need to understand the following things:
//
// 1. Some points are given in the plane, with their x and y coordinates. The graph is not
// given directly, so we need to assume that the graph is given implicitly.
//
// 2. We need to connect using minimum cable, so it means that all the nodes are reachable
// from each other and then we need to find the minimum spanning tree.
//
// 3. Weights of each edge is also not given directly, we need to apply the simple formula
// and calculate the weight of each edge.
//
// So as the preprocessing step, we need to create the graph with all the edges having the
// weights.
//
// Next we can apply for kruskal algorithm using rank, which needs the notion of a node
// having a rank and a parent.
double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  //write your code here
  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
