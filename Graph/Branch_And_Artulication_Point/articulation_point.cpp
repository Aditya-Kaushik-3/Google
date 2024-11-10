/*
 * Problem: Find Articulation Points in a Graph.
 * 
 * Articulation points (or cut vertices) in an undirected graph are those vertices
 * that, when removed, increase the number of connected components of the graph.
 * 
 * Approach:
 * 1. **DFS Traversal with Timer and Low Link Values**: We will use Depth First Search (DFS) to traverse the graph.
 * 2. **Timer**: A unique timer for each node to keep track of the discovery time.
 * 3. **Low Link Value**: For each node, we calculate the lowest discovery time reachable by its subtree.
 * 4. **Articulation Point Detection**: 
 *      - If for a node `u`, a child `v` satisfies the condition `low[v] >= timer[u]`, then `u` is an articulation point.
 *      - For the root node, it becomes an articulation point if it has more than one child in DFS traversal.
 * 
 * Key Ideas:
 * - We use two arrays: `timer[]` for discovery times and `low[]` for low-link values.
 * - If for any node, the lowest discovery time reachable from its subtree is greater than or equal to the discovery time of the node itself, that node is an articulation point.
 * - A node is an articulation point if, removing it would split the graph into more connected components.
 * 
 * Algorithm Steps:
 * 1. Initialize arrays for `timer[]`, `low[]`, and visited nodes `vis[]`.
 * 2. Traverse all nodes with DFS starting from each unvisited node.
 * 3. During DFS:
 *    - For each child node, compute `low` values recursively.
 *    - Update the articulation point condition for each node.
 * 4. After the DFS, return a list of all articulation points.
 * 5. If no articulation point exists, return [-1].


Time Complexity:
O(N + E), where N is the number of nodes and E is the number of edges, as the algorithm performs a single DFS traversal.
Space Complexity:
O(N + E) for the adjacency list and auxiliary arrays used during DFS.


 */

class Solution {
private:
    int timerr = 0;  // Global timer to maintain discovery time of nodes
    
    // DFS function to compute low-link values and articulation points
    void dfs(int node, int parent, vector<int>& timer, vector<int>& low, vector<int>& vis, vector<int> adj[], vector<int>& ap) {
        vis[node] = 1;            // Mark the current node as visited
        timer[node] = low[node] = timerr;  // Set the discovery time and low-link value
        timerr++;                 // Increment the timer for the next node
        
        int child = 0;            // To count the number of children of the current node

        // Traverse all adjacent nodes (children)
        for (auto it : adj[node]) {
            if (it == parent) continue;  // Ignore the parent node to avoid going backward in DFS
            
            if (vis[it] == 0) {  // If the node is unvisited, perform DFS on it
                dfs(it, node, timer, low, vis, adj, ap);  // Recurse to the child node
                low[node] = min(low[node], low[it]);  // Update low-link value of the current node

                // If the low-link value of the child node is greater than or equal to the discovery time of the current node
                // then the current node is an articulation point
                if (low[it] >= timer[node] && parent != -1) {
                    ap[node] = 1;  // Mark the current node as an articulation point
                }
                child++;  // Increment the number of children
            } else {
                // If the node is already visited, update the low-link value based on the back edge
                low[node] = min(low[node], timer[it]);
            }
        }

        // Special case for the root node: if it has more than one child in DFS, it's an articulation point
        if (child > 1 && parent == -1) {
            ap[node] = 1;
        }
    }

public:
    // Function to find all articulation points in the graph
    vector<int> articulationPoints(int n, vector<int> adj[]) {
        vector<int> vis(n, 0);   // To track visited nodes
        vector<int> timer(n);     // Discovery time of each node
        vector<int> low(n);       // Lowest discovery time reachable from the node
        vector<int> ap(n, 0);     // Array to mark articulation points
        
        // Start DFS traversal from all unvisited nodes
        for (int i = 0; i < n; i++) {
            if (vis[i] == 0) {
                dfs(i, -1, timer, low, vis, adj, ap);  // Start DFS from unvisited node
            }
        }

        // Collect all nodes that are articulation points
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (ap[i] == 1) {
                ans.push_back(i);  // Add node to result if it is an articulation point
            }
        }

        // If no articulation points found, return [-1]
        if (ans.empty()) return {-1};
        
        return ans;  // Return the list of articulation points
    }
};
