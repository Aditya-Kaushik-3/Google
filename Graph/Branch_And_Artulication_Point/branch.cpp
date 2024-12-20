/*
 * Problem: Find Critical Connections in a Network (Bridges in an Undirected Graph).
 * 
 * A critical connection (or bridge) in an undirected graph is an edge that, when removed, 
 * causes an increase in the number of connected components in the graph.
 * 
 * Approach:
 * 1. **DFS Traversal with Time and Low-link Values**:
 *    - We'll perform Depth-First Search (DFS) to explore the graph.
 *    - During DFS, we track two things:
 *      - `time[]`: The discovery time when a node is first visited.
 *      - `low[]`: The lowest discovery time reachable from a node, including back edges.
 * 
 * 2. **Bridge Detection**:
 *    - For every edge (u, v), if `low[v] > time[u]`, then the edge (u, v) is a bridge.
 *    - This is because if `v` cannot reach a node with a lower discovery time than `u`, removing the edge (u, v) will disconnect the graph.
 *    
 * 3. **DFS Execution**:
 *    - We start the DFS from any node (typically node 0).
 *    - For each unvisited node, we recursively perform DFS and update the `low[]` values.
 *    - If the condition for a bridge is satisfied, we add that edge to the result list.
 * 
 * Algorithm Steps:
 * 1. Build the adjacency list for the graph from the given edge list `connections`.
 * 2. Initialize arrays for visited status, discovery times (`time[]`), and low-link values (`low[]`).
 * 3. Perform DFS from an arbitrary starting node (node 0).
 * 4. After the DFS traversal, any edge (u, v) that satisfies `low[v] > time[u]` is a critical connection.
 * 5. Return all such critical connections.
 * 
 * Time Complexity:
 * - **O(N + E)**, where N is the number of nodes and E is the number of edges. 
 *   The DFS visits each node and edge once.
 * 
 * Space Complexity:
 * - **O(N + E)** for the adjacency list, as we store each edge once, plus additional space for the visited, time, and low arrays.
 */

class Solution {
private:
    int timer = 0;  // Global timer for discovery time

    // Helper DFS function to explore the graph and find bridges
    void dfs(int node, int parent, vector<int> adj[], vector<int>& vis, vector<int>& low, vector<int>& time, vector<vector<int>>& bridge) {
        vis[node] = 1;         // Mark the current node as visited
        low[node] = time[node] = timer;  // Set discovery time and low-link value
        timer++;               // Increment the timer for the next node
        
        // Explore all the adjacent nodes (children)
        for (auto it : adj[node]) {
            if (it == parent) continue;  // Skip the parent node to avoid backward traversal
            
            if (vis[it] == 0) {  // If the child node is not visited, perform DFS on it
                dfs(it, node, adj, vis, low, time, bridge);
                
                // After DFS on the child node, update the low-link value of the current node
                low[node] = min(low[node], low[it]);

                // If the low-link value of the child node is greater than the discovery time of the current node,
                // it means the edge (node, it) is a bridge
                if (low[it] > time[node]) {
                    bridge.push_back({node, it});  // Store the bridge (critical connection)
                }
            }
            else {
                // If the adjacent node is already visited, update the low-link value of the current node
                low[node] = min(low[node], time[it]);
            }
        }
    }

public:
    // Function to find all critical connections (bridges) in the graph
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<int> adj[n];  // Adjacency list for the graph
        
        // Build the adjacency list from the given connections
        for (auto it : connections) {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }

        vector<int> vis(n, 0);     // Visited array to track the visited nodes
        vector<int> time(n, -1);   // Discovery time for each node
        vector<int> low(n, -1);    // Low-link values for each node
        vector<vector<int>> bridge;  // To store the result (critical connections)
        
        // Start DFS from node 0 (arbitrary starting point)
        dfs(0, -1, adj, vis, low, time, bridge);
        
        return bridge;  // Return the list of critical connections (bridges)
    }
};
