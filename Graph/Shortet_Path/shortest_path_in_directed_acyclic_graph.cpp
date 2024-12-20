/*
 * Problem: Find the Shortest Path in a Directed Acyclic Graph (DAG) using Topological Sort.
 *
 * Approach:
 * 1. **Topological Sort**:
 *    - First, we perform a **topological sort** of the graph. This ensures that we process each node after all its dependencies (i.e., all edges pointing to the node are processed before the node itself).
 *    - A topological sort is possible only in a Directed Acyclic Graph (DAG).
 *
 * 2. **Relaxation Process**:
 *    - Once we have the topologically sorted nodes, we can use the relaxation technique to update the shortest path distances.
 *    - Start from the source node (node 0) and update the distances to other nodes by iterating over the adjacent nodes in the topologically sorted order.
 *    - If a shorter path is found (i.e., `dist[u] + weight < dist[v]`), update the distance to node `v`.
 *
 * Time Complexity:
 * - **O(N + M)**, where N is the number of nodes and M is the number of edges in the graph.
 *   - Topological sort takes **O(N + M)** time.
 *   - The relaxation step also takes **O(N + M)** time as we process all edges.
 *
 * Space Complexity:
 * - **O(N + M)** for storing the graph (adjacency list), the visited array, and the stack for the topological sort.
 */

class Solution {
private:
	// Helper function to perform Topological Sort using DFS
	void topoSort(int node, vector<pair<int, int>> adj[], int vis[], stack<int>& st) {
		vis[node] = 1;  // Mark the node as visited

		// Visit all the adjacent nodes
		for (auto it : adj[node]) {
			int v = it.first;
			if (!vis[v]) {  // If the adjacent node is unvisited
				topoSort(v, adj, vis, st);  // Recurse on the unvisited node
			}
		}

		// Push the node to the stack after visiting all its neighbors
		st.push(node);
	}

public:
	// Function to find the shortest path in a DAG
	vector<int> shortestPath(int N, int M, vector<vector<int>>& edges) {
		// Step 1: Create an adjacency list from the given edges
		vector<pair<int, int>> adj[N];
		for (int i = 0; i < M; i++) {
			int u = edges[i][0];
			int v = edges[i][1];
			int wt = edges[i][2];
			adj[u].push_back({v, wt});  // Store the edge (v, wt) in the adjacency list of u
		}

		// Step 2: Perform Topological Sort
		int vis[N] = {0};  // Initialize visited array to track visited nodes
		stack<int> st;  // Stack to store the topologically sorted nodes

		// Perform DFS to get the topological ordering of the nodes
		for (int i = 0; i < N; i++) {
			if (!vis[i]) {
				topoSort(i, adj, vis, st);  // Call DFS for unvisited nodes
			}
		}

		// Step 3: Initialize the distance vector with infinity (1e9)
		vector<int> dist(N, 1e9);  // Set all distances to a large value
		dist[0] = 0;  // The distance from the source (node 0) to itself is 0

		// Step 4: Relax edges based on the topological order
		while (!st.empty()) {
			int node = st.top();  // Get the next node in topological order
			st.pop();  // Remove the node from the stack

			// Iterate through all the adjacent nodes of the current node
			for (auto it : adj[node]) {
				int v = it.first;
				int wt = it.second;

				// If a shorter path is found, update the distance
				if (dist[node] + wt < dist[v]) {
					dist[v] = dist[node] + wt;
				}
			}
		}

		// Step 5: Replace unreachable nodes with -1
		for (int i = 0; i < N; i++) {
			if (dist[i] == 1e9) dist[i] = -1;  // If the distance is still infinity, set it to -1
		}

		return dist;  // Return the distance array with the shortest paths
	}
};

