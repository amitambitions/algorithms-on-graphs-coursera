#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::numeric_limits;

// Check that we are making a heap and using the node for our heap algorithm. When we 
// choose source vertex, then we need to see which is the next vertex to be promoted to
// the root, so we need to know its index as well as the weight.
struct Node {
  int index, distance;
  Node(int index = 0, int distance = 0): index(index), distance(distance) {}
};

// By default priority_queue keeps the value with highest value as the root i.e. it makes
// max-heap and we need a min-heap. So we just make a comparator to reverse the order.
struct cmp {
	bool operator()(Node first, Node second){
		return first.distance > second.distance;
	}
};

// Ideally this program gives the cost matrix separately but that is waste of cycles it seems.
// TODO - 
// 1. merge into single vector
// 2. refresh about std::pairs as that could simplify the solution here.
int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code here
  vector<int> dist(adj.size(), numeric_limits<int>::max());
  dist[s] = 0;
  
  // Custom priority queue.
  priority_queue<Node, vector<Node>, cmp> pq;
  
  // push the source vertex.
  pq.push(Node(s, dist[s]));
  while(!pq.empty()) {
	Node u = pq.top();
	pq.pop();
	int u_index = u.index;
	
	// Relax each edge associated with given node.
    for (int i = 0; i < adj[u_index].size(); i++) {
	  int v = adj[u_index][i];
	  if(dist[v] > dist[u_index] + cost[u_index][i]) {
	    dist[v] = dist[u_index] + cost[u_index][i];
        pq.push(Node(v, dist[v])); 
	  }
	}	
  }
  
  if(dist[t] == numeric_limits<int>::max())
    return -1;
    
  return dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
