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
struct node {
  int parent;
  int rank;
  int x;
  int y;
	
  node(int a, int b, int c = -1, int d = 0) {
    x = a;
    y = b;
    parent = c;
    rank = d;
  }
};

struct edge {
  int u;
  int v;
  double weight;
  
  edge(int a, int b, double c) {
    u = a;
    v = b;
    weight = c;
  }
};

bool cmp(edge a, edge b) {
  return a.weight < b.weight;
}

void make_set(int i, vector<node> &nodes, vector<int> &x, vector<int> &y) {
  nodes.push_back(node(x[i], y[i], i));
}

double weight(int x1, int y1, int x2, int y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int Find(int i, vector<node> &nodes) {
  if (i != nodes[i].parent) {
    nodes[i].parent = Find(nodes[i].parent, nodes);
  }
  return nodes[i].parent;
}

// TODO: further optimizations:
// 1) suppose the graph is really big, then we do not want to call Find() again and again.
// Check that we call union only when we have already calculated Find() of u and v and we
// know that it is not same. So, just pass those values to union functions and we will not
// need to call Find() again.
// 2) We can wrap the algorithm inside a class and then we dont need to pass nodes vector
// every time.
// 3) Need to check if some advanced constructs of C++11 can be used here.
void Union(int u, int v, vector<node> &nodes) {
  int r1 = Find(u, nodes);
  int r2 = Find(v, nodes);
  if (r1 != r2) {
    if (nodes[r1].rank > nodes[r2].rank) {
      nodes[r2].parent = r1;
    } else {
      nodes[r1].parent = r2;
      if (nodes[r1].rank == nodes[r2].rank) {
        nodes[r2].rank++;
      }
    }
  }
}

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  //write your code here
  int n = x.size();
  
  // TODO: always use range based for loops whenever C++11 or higher is supported.
  vector<node> nodes;
  for (int i = 0; i < n; i++) {
	make_set(i, nodes, x, y);
  }
  
  // Creating this vector of edges is the whole crux. Initially we may feel that we are
  // creating a nested for loop but check that this is an undirected graph and we need
  // a link between every 2 nodes to see the best possible connections. We have 5 nodes,
  // then we need links like (0,1), (0,2)...(0,4) then (1,2)..(1,4) etc.
  vector<edge> edges;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      edges.push_back(edge(i, j, weight(x[i], y[i], x[j], y[j])));
    }
  }
  
  // TODO: use std::function<> or lambdas for comparison function.
  std::sort(edges.begin(), edges.end(), cmp);
  for (int i = 0; i < edges.size(); i++) {
    edge current_edge = edges[i];
    int u = current_edge.u;
    int v = current_edge.v;
    if (Find(u, nodes) != Find(v, nodes)) {
      result += current_edge.weight;
      Union(u, v, nodes);
    }
  }
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
