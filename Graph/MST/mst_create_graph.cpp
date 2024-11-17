#include <bits/stdc++.h>
using namespace std;

/*
    Prim's Algorithm to find Minimum Spanning Tree (MST) and create the MST graph.
    
    The algorithm finds the minimum spanning tree of a connected, weighted, undirected graph.
    It starts with an arbitrary node and grows the MST by adding the shortest edge from the frontier.

    Steps:
    1. Initialize a priority queue to store edges with weights.
    2. Mark all nodes as unvisited.
    3. Push the first node into the priority queue with a weight of 0 (starting node).
    4. Continue adding the smallest edge from the frontier until all nodes are visited.
    5. Track the MST edges and construct the MST graph.

    Time Complexity:
    - **O(E log V)** where V is the number of vertices and E is the number of edges.
      - For each edge, we push or pop it from the priority queue, which takes **O(log V)** time.
      - There are **E** edges in total.

    Space Complexity:
    - **O(V + E)**: The space complexity is dominated by the adjacency list (O(V + E)) and the priority queue (O(V)).
*/

vector<vector<int>> createMSTGraph(int V, vector<vector<int>> adj[]) {
    // Initialize the priority queue with a pair of (weight, node).
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // Vector to track visited nodes, initially all nodes are unvisited.
    vector<int> vis(V, 0);
    
    // New adjacency list for the MST graph.
    vector<vector<int>> mstGraph(V);
    
    // Start with node 0 and its weight 0.
    pq.push({0, 0});
    
    while (!pq.empty()) {
        // Extract the node with the minimum weight from the priority queue.
        auto it = pq.top();
        pq.pop();
        
        int node = it.second;  // The node with the minimum weight.
        int wt = it.first;     // The weight of the edge to this node.
        
        // If the node is already visited, we skip it.
        if (vis[node] == 1) continue;
        
        // Mark the node as visited.
        vis[node] = 1;
        
        // Explore all adjacent nodes (neighbors of the current node).
        for (auto itr : adj[node]) {
            int adj_node = itr[0];  // Adjacent node.
            int adj_wt = itr[1];    // Weight of the edge to the adjacent node.
            
            // If the adjacent node is not visited, push it to the priority queue.
            if (vis[adj_node] != 1) {
                pq.push({adj_wt, adj_node});
                
                // Add the edge to the MST graph (undirected graph, so add both directions)
                mstGraph[node].push_back(adj_node);
                mstGraph[adj_node].push_back(node);
            }
        }
    }
    
    return mstGraph;  // Return the MST graph as an adjacency list.
}

void printGraph(int V, vector<vector<int>> graph[]) {
    for (int i = 0; i < V; i++) {
        cout << "Node " << i << ": ";
        for (auto& edge : graph[i]) {
            cout << edge << " ";
        }
        cout << endl;
    }
}

int main() {
    // Example graph as an adjacency list:
    int V = 5;  // Number of vertices
    vector<vector<int>> adj[V];
    
    // Add edges to the graph (undirected, so we add both directions)
    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2});
    
    adj[0].push_back({3, 6});
    adj[3].push_back({0, 6});
    
    adj[1].push_back({2, 3});
    adj[2].push_back({1, 3});
    
    adj[1].push_back({3, 8});
    adj[3].push_back({1, 8});
    
    adj[2].push_back({4, 7});
    adj[4].push_back({2, 7});
    
    adj[3].push_back({4, 9});
    adj[4].push_back({3, 9});
    
    // Create the MST graph
    vector<vector<int>> mstGraph = createMSTGraph(V, adj);
    
    // Print the MST graph
    cout << "MST Graph (Adjacency List):" << endl;
    printGraph(V, mstGraph);
    
    return 0;
}
