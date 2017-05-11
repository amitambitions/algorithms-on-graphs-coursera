#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
  // Algorithm is pretty simple. While we traverse and perform BFS then every time
  // we see a node then if the color of that node is same as that of the parent then
  // the graph is not bipartite and we can stop the flow and return 0. If the color is
  // not set then it means that the node is not visited and we can set its color to the
  // opposite of its parents color. The value 1 is used to indicate first color is
  // assigned and value 0 indicates second color is assigned.
  //
  // NOTE - in this algorithm we do not need to find the path, so we will not do any
  // extra computation for keeping the distances.
  vector<int> color(adj.size(), -1);
  
  // Assign first color to the source vertex
  color[0] = 1;
  
  // Create a queue (FIFO) of vertex numbers and enqueue source vertex for BFS traversal.
  // Let the starting vertex to be vertex number 0.
  queue<int> queue;
  queue.push(0);
  
  // Run while there are vertices in queue (Similar to BFS)
  while(!queue.empty()) {
	// Dequeue a vertex from queue
    int u = queue.front();
	queue.pop();
	   
    // Find all non-colored adjacent vertices
    for(int i=0; i < adj[u].size(); ++i) {
      int v = adj[u][i];
      // Destination v is colored with same color as u
      if (colorArr[v] == color[u])
        return 0;
        
	  // Destination v is not colored
      else if (color[v] == -1) {
        // Assign alternate color to this adjacent v of u
        color[v] = 1- color[u];
		queue.push(v);
	  }
	}
  }
  
  // If we reach here, then it means that the graph is bipartite and all the adjacent
  // nodes are colored with different color.
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
