
class Solution {
public:
	/*
	 * Bellman-Ford Algorithm to find the shortest path from a source vertex to all other vertices
	 * in a weighted graph, including the ability to detect negative weight cycles.
	 *
	 * Steps:
	 * 1. Initialize the distance array `dist[]` with a large value (infinity). Set the distance
	 *    to the source vertex to 0.
	 * 2. Perform relaxation for all edges V-1 times. Relaxation means updating the distance to
	 *    a vertex if a shorter path is found.
	 * 3. After the V-1 iterations, check for negative weight cycles. If any edge can still be relaxed,
	 *    it indicates the presence of a negative cycle and return `-1`.
	 * 4. If no negative cycle is detected, return the final shortest distances.
	 *
	 * Time Complexity:
	 * - The relaxation step involves looping over all edges **V - 1** times. So, the time complexity
	 *   is **O(V * E)** where V is the number of vertices and E is the number of edges.
	 * - After the V-1 iterations, we check for negative cycles by iterating over all edges again, which
	 *   takes **O(E)**.
	 * - Therefore, the total time complexity is **O(V * E)**.
	 *
	 * Space Complexity:
	 * - We use a distance array `dist[]` of size **V** to store the shortest distances.
	 * - Thus, the space complexity is **O(V)**.
	 */

	vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
		// Step 1: Initialize the distance array with infinity (1e8).
		vector<int> dist(V, 1e8);  // Large value represents infinity
		dist[src] = 0;  // Distance to the source is 0

		// Step 2: Perform relaxation for all edges (V - 1) times
		// Relax all edges for V-1 iterations.
		for (int i = 0; i < V - 1; i++) {
			for (auto it : edges) {
				int u = it[0];  // Source vertex of the edge
				int v = it[1];  // Destination vertex of the edge
				int wt = it[2]; // Weight of the edge
				// If the distance to u is not infinity and the edge offers a shorter path to v
				if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
					dist[v] = dist[u] + wt;  // Relax the edge
				}
			}
		}

		// Step 3: Check for negative-weight cycles
		// If an edge can still be relaxed, it means there is a negative cycle
		for (auto it : edges) {
			int u = it[0];
			int v = it[1];
			int wt = it[2];
			// If the distance to v can still be updated, we have a negative cycle
			if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
				return { -1}; // Negative cycle detected
			}
		}

		// Step 4: Return the shortest distance array
		return dist;
	}
};
