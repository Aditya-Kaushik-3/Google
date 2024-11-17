#include <bits/stdc++.h>
using namespace std;

/*
    Prim's Algorithm for Minimum Spanning Tree (MST)
    
    The algorithm finds the minimum spanning tree of a connected, weighted, undirected graph.
    It starts with an arbitrary node and grows the MST by adding the shortest edge from the frontier.

    Steps:
    1. Initialize a priority queue to store edges with weights.
    2. Mark all nodes as unvisited.
    3. Push the first node into the priority queue with a weight of 0 (starting node).
    4. Continue adding the smallest edge from the frontier until all nodes are visited.

    Time Complexity:
    - **O(E log V)** where V is the number of vertices and E is the number of edges.
      - For each edge, we push or pop it from the priority queue, which takes **O(log V)** time.
      - There are **E** edges in total.

    Space Complexity:
    - **O(V + E)**: The space complexity is dominated by the adjacency list (O(V + E)) and the priority queue (O(V)).
*/

int spanningTree(int V, vector<vector<int>> adj[]) {
    // Initialize the priority queue with a pair of (weight, node).
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // Vector to track visited nodes, initially all nodes are unvisited.
    vector<int> vis(V, 0);
    
    // Start with node 0 and its weight 0.
    pq.push({0, 0});
    int ans = 0;  // Variable to store the total weight of the MST.
    
    while (!pq.empty()) {
        // Extract the node with the minimum weight from the priority queue.
        auto it = pq.top();
        pq.pop();
        
        int node = it.second;  // The node with the minimum weight.
        int wt = it.first;  // The weight of the edge to this node.
        
        // If the node is already visited, we skip it.
        if (vis[node] == 1) continue;
        
        // Mark the node as visited.
        vis[node] = 1;
        
        // Add the weight of the current edge to the MST.
        ans += wt;
        
        // Explore all adjacent nodes (neighbors of the current node).
        for (auto itr : adj[node]) {
            int adj_node = itr[0];  // Adjacent node.
            int adj_wt = itr[1];  // Weight of the edge to the adjacent node.
            
            // If the adjacent node is not visited, push it to the priority queue.
            if (vis[adj_node] != 1) {
                pq.push({adj_wt, adj_node});
            }
        }
    }
    
    return ans;  // Return the total weight of the MST.
}
