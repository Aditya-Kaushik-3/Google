
/*
 * Problem: Find the Shortest Path in an Unweighted Graph using BFS.
 *
 * Approach:
 * 1. **Graph Representation**:
 *    - The graph is represented using an adjacency list. We convert the given edge list into this adjacency list.
 *
 * 2. **Breadth-First Search (BFS)**:
 *    - We use **BFS** to find the shortest path in an unweighted graph, as BFS naturally explores nodes level by level (i.e., distance-wise).
 *    - BFS is ideal for unweighted graphs because it guarantees that the first time a node is reached, it is reached via the shortest path.
 *
 * 3. **Distance Array**:
 *    - We initialize a `dist[]` array to store the shortest distance from the source node to all other nodes.
 *    - The distance of the source node to itself is set to `0`, and all other nodes are initially set to a large value (`1e9`), indicating they are not yet reachable.
 *
 * 4. **BFS Traversal**:
 *    - We use a queue to perform BFS. For each node, we explore all its neighbors. If a shorter path to a neighbor is found, we update its distance and push it to the queue.
 *
 * 5. **Final Answer**:
 *    - Once BFS is completed, if a node is still unreachable (i.e., its distance is still `1e9`), we mark its distance as `-1` to indicate it's not reachable from the source node.

 * Time Complexity:
 * - **O(N + M)**: BFS visits each node and edge at most once. `N` is the number of nodes and `M` is the number of edges.
 *
 * Space Complexity:
 * - **O(N + M)**: The space required for storing the adjacency list (graph representation) is **O(N + M)**. We also use a queue and a distance array, both of size **O(N)**.
 */

class Solution {
public:
	vector<int> shortestPath(vector<vector<int>>& edges, int N, int M, int src) {
		// Step 1: Create the adjacency list from the edge list
		vector<int> adj[N];  // Adjacency list representation of the graph
		for (auto it : edges) {
			adj[it[0]].push_back(it[1]);  // Add edge from it[0] to it[1]
			adj[it[1]].push_back(it[0]);  // Since the graph is undirected, add the reverse edge as well
		}

		// Step 2: Initialize distance array and set all nodes' distance to infinity (1e9)
		vector<int> dist(N, 1e9);  // Distance array to store shortest path from source to each node
		dist[src] = 0;  // Distance to the source node is 0

		// Step 3: Perform BFS starting from the source node
		queue<int> q;  // Queue to manage the BFS traversal
		q.push(src);  // Push the source node to the queue

		while (!q.empty()) {
			int node = q.front();  // Get the front node from the queue
			q.pop();  // Pop the node from the queue

			// Explore all adjacent nodes (neighbors) of the current node
			for (auto it : adj[node]) {
				// If a shorter path is found, update the distance and push the node to the queue
				if (dist[node] + 1 < dist[it]) {
					dist[it] = dist[node] + 1;  // Update the distance of the neighboring node
					q.push(it);  // Push the neighboring node into the queue for further exploration
				}
			}
		}

		// Step 4: Prepare the final answer, setting unreachable nodes' distance to -1
		vector<int> ans(N, -1);  // Initialize the answer array with -1 (unreachable nodes)
		for (int i = 0; i < N; i++) {
			if (dist[i] != 1e9) {  // If the node is reachable, update its distance
				ans[i] = dist[i];
			}
		}

		return ans;  // Return the final array with shortest distances from the source node
	}
};
