
class Solution {
public:
	/*
	 * Floyd-Warshall Algorithm to find the shortest distance between all pairs of vertices.
	 *
	 * Steps:
	 * 1. Initialize the distance matrix:
	 *    - If there is no direct path between two nodes (i.e., matrix[i][j] == -1), set the distance to a large value (infinity).
	 *    - If a node is the same as itself (i.e., i == j), set the distance to 0.
	 * 2. Perform the Floyd-Warshall algorithm:
	 *    - For each possible intermediate vertex `k`, check if going from vertex `i` to vertex `j` through `k` results in a shorter path.
	 *      Update the matrix with the new shorter distances.
	 * 3. Check for negative cycles:
	 *    - If any `matrix[i][i] < 0`, it indicates the presence of a negative cycle.
	 *    - In this case, return {-1} to indicate the negative cycle.
	 * 4. Convert distances that remain infinity (`1e9`) back to `-1` to represent no path.
	 * 5. Return the modified matrix with shortest distances between all pairs of vertices.
	 *
	 * Time Complexity:
	 * - The algorithm has three nested loops (i, j, k), each running from 0 to n (where n is the number of vertices).
	 * - Thus, the time complexity is **O(n^3)** where n is the number of vertices in the graph.
	 *
	 * Space Complexity:
	 * - The space complexity is **O(n^2)** as the algorithm uses a distance matrix of size n x n to store the shortest distances.
	 */

	void shortest_distance(vector<vector<int>>& matrix) {
		int n = matrix.size();  // Number of vertices (nodes)

		// Step 1: Initialize the distance matrix
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (matrix[i][j] == -1) {
					matrix[i][j] = 1e9;  // No direct path between i and j, set distance to infinity
				}
				if (i == j) {
					matrix[i][j] = 0;  // Distance from a node to itself is 0
				}
			}
		}

		// Step 2: Apply the Floyd-Warshall Algorithm
		// Try every possible intermediate vertex `k`
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					// Update the distance if a shorter path is found through vertex `k`
					matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
				}
			}
		}

		// Step 3: Check for negative cycles
		for (int i = 0; i < n; ++i) {
			if (matrix[i][i] < 0) {
				// If matrix[i][i] < 0, it indicates a negative weight cycle
				return;  // In this case, we return early, as it's impossible to find valid shortest paths
			}
		}

		// Step 4: Replace infinite distances (1e9) back to -1 (to indicate no path)
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (matrix[i][j] == 1e9) {
					matrix[i][j] = -1;  // No path exists
				}
			}
		}
	}
};
