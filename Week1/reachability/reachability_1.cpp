#include <iostream>
#include <vector>

using std::vector;
using std::pair;

int explore(const vector<vector<int> > &adj, int x, int y, vector<int> &visited) {
	if (x == y) {
		return 1;
	}	
	visited[x] = 1;
	for (vector<int>::const_iterator it = adj[x].begin(); it != adj[x].end(); ++it) {
	  if (!visited[*it]) {
	    if (explore(adj, *it, y, visited)) {
	      return 1;
	    }
	  }
	}
	return 0;
}


int reach(vector<vector<int> > &adj, int x, int y) {
  vector<int> visited(adj.size());
  return explore(adj, x, y, visited);
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
