
/*
 * Problem: Find the Shortest Path from a Source Vertex in a Weighted Graph using Dijkstra's Algorithm.
 *
 * Approach:
 * 1. **Graph Representation**:
 *    - The graph is represented as an adjacency list, where each node points to a list of its neighbors and their respective edge weights.
 *
 * 2. **Priority Queue (Min-Heap)**:
 *    - We use a **priority queue** (min-heap) to efficiently get the node with the minimum distance during the process of exploring the graph.
 *    - Each entry in the priority queue is a pair: `{distance, node}`. The priority queue ensures that we always process the node with the smallest known distance first.
 *
 * 3. **Dijkstra's Algorithm**:
 *    - Initialize a distance array `distTo[]` where `distTo[S]` is set to `0` (distance from the source to itself) and all other nodes are set to infinity (`INT_MAX`).
 *    - Start by pushing the source node into the priority queue.
 *    - At each step, pop the node with the minimum distance from the priority queue and explore its neighbors.
 *    - For each neighbor, if a shorter path to the neighbor is found (i.e., `distTo[node] + weight < distTo[neighbor]`), update the neighbor's distance and push it into the priority queue.
 *
 * 4. **Final Output**:
 *    - Once all nodes are processed, the `distTo[]` array contains the shortest distances from the source node `S` to all other nodes. If a node is unreachable, its distance remains `INT_MAX`.
 *
 * Time Complexity:
 * - **O(E * log V)**: since E is large than V else O((V+E) * log V)
 *   - **O(log V)** is the time to insert or remove an element from the priority queue.
 *   - **V** is the number of vertices.
 *   - **E** is the number of edges, since we process each edge exactly once.
 *
 * Space Complexity:
 * - **O(V + E)**:
 *   - **O(V)** for storing the distance array (`distTo[]`).
 *   - **O(V)** for the priority queue.
 *   - **O(E)** for the adjacency list.



 WE CAN NOT USE WITH NEGATIVE WEIGHTS AS IT WILL GO IN IN FINITE LOOP
 */

class Solution
{
public:
	// Function to find the shortest distance of all the vertices
	// from the source vertex S.
	vector<int> dijkstra(int V, vector<vector<int>> adj[], int S)
	{
		// Step 1: Create a priority queue (min-heap) for {distance, node} pairs
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

		// Step 2: Initialize distance array with INT_MAX (infinity), except for the source node
		vector<int> distTo(V, INT_MAX);
		distTo[S] = 0;

		// Step 3: Push the source node with distance 0 into the priority queue
		pq.push({0, S});

		// Step 4: Process the graph
		while (!pq.empty())
		{
			// Extract the node with the smallest distance from the priority queue
			int node = pq.top().second;  // Node with minimum distance
			int dis = pq.top().first;    // Distance of that node from the source
			pq.pop();

			// Step 5: Explore all adjacent nodes (neighbors)
			for (auto it : adj[node])
			{
				int v = it[0];  // Neighbor node
				int w = it[1];  // Edge weight (distance from node to v)

				// Step 6: If a shorter path to the neighbor is found, update its distance
				if (dis + w < distTo[v])
				{
					distTo[v] = dis + w;
					pq.push({dis + w, v});  // Push the updated distance and node into the queue
				}
			}
		}

		// Step 7: Return the final distance array containing shortest distances from source to all nodes
		return distTo;
	}
};
