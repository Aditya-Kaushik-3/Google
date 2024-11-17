#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Find the number of operations needed to make a graph fully connected
    using the Disjoint Set (Union-Find) data structure.

    The task is to determine the number of additional edges required to connect all the disjoint sets
    in an undirected graph. If it's impossible to connect all components (e.g., due to lack of edges),
    the function should return -1.

    Approach:
    - We represent the graph as a series of edges between nodes.
    - We use the **Disjoint Set** (or **Union-Find**) data structure to track connected components of the graph.
    - The idea is to iterate over the edges:
        - If two nodes are already connected (i.e., they belong to the same set), we count this as an **extra edge**.
        - Otherwise, we **union** the two sets (merge the two components) to form a new connected component.
    - At the end, the number of **disjoint sets** remaining will tell us how many operations (additional edges) are required to make the graph fully connected.

    Steps:
    1. Initialize a Disjoint Set (Union-Find) with `n` nodes.
    2. Traverse through each edge in the graph:
        - If the nodes of the edge are already in the same set, count it as an extra edge.
        - Otherwise, union the sets containing the two nodes.
    3. Count the number of disjoint sets (connected components) remaining.
    4. The number of operations required to connect the graph is `cntC - 1`, where `cntC` is the number of disjoint sets.
    5. If there are more extra edges than the required operations, return the number of operations. Otherwise, return -1.

    Time Complexity:
    - **Union and Find Operations**: The time complexity for both `find` and `union` operations is **O(α(N))**, where α is the inverse Ackermann function. This is nearly constant for all practical input sizes.
    - **Overall Time Complexity**: Since we perform these operations for each edge, the overall time complexity is **O(E * α(N))**, where E is the number of edges in the graph.
    
    Space Complexity:
    - We store `parent[]`, `size[]`, and `rank[]` arrays, each of size **O(N)**, where N is the number of nodes in the graph.
    - Thus, the space complexity is **O(N)**.

*/

class DisjointSet {
public:
    vector<int> rank, parent, size;
    
    // Constructor: Initializes the parent, size, and rank arrays
    DisjointSet(int n) {
        rank.resize(n + 1, 0);    // Rank is used for optimizing union operation (not used here explicitly)
        parent.resize(n + 1);     // Parent array: stores the representative (root) of each set
        size.resize(n + 1, 1);    // Size array: stores the size of each set (used in union by size)
        
        // Initially, each node is its own parent, and the size of each set is 1
        for (int i = 0; i <= n; i++) {
            parent[i] = i;    // Each node is initially its own parent
            size[i] = 1;      // The size of each set is 1 initially (each node is in its own set)
        }
    }

    // Function to find the representative (root) of the set containing 'node'
    int findUPar(int node) {
        if (node == parent[node]) 
            return node;  // If the node is its own parent, return the node
        // Path Compression: Make each node in the path point directly to the root
        return parent[node] = findUPar(parent[node]);
    }

    // Union by size: Merge the set containing 'u' and 'v' by size
    void unionBySize(int u, int v) {
        // Find the representatives (roots) of the sets containing 'u' and 'v'
        int rootU = findUPar(u);
        int rootV = findUPar(v);

        // If the sets are already connected (i.e., their representatives are the same), do nothing
        if (rootU == rootV) return;

        // Union by size: Merge the smaller set into the larger one
        if (size[rootU] < size[rootV]) {
            parent[rootU] = rootV;   // Make root of 'u' point to root of 'v'
            size[rootV] += size[rootU];  // Increase size of 'v' by the size of 'u'
        } else {
            parent[rootV] = rootU;   // Make root of 'v' point to root of 'u'
            size[rootU] += size[rootV];  // Increase size of 'u' by the size of 'v'
        }
    }
};

class Solution {
public:
    int Solve(int n, vector<vector<int>>& edge) {
        // Initialize Disjoint Set with 'n' nodes
        DisjointSet ds(n);

        int cntExtras = 0;  // To count the number of extra edges (edges that don't contribute to new connections)
        
        // Step 1: Process each edge in the graph
        for (auto it : edge) {
            int u = it[0];  // Source vertex of the edge
            int v = it[1];  // Destination vertex of the edge

            // If u and v are already in the same set, count this as an extra edge
            if (ds.findUPar(u) == ds.findUPar(v)) {
                cntExtras++;
            }
            // Otherwise, union the sets containing u and v to connect them
            else {
                ds.unionBySize(u, v);
            }
        }

        // Step 2: Count the number of disjoint sets (connected components)
        int cntC = 0;  // To count the number of disjoint sets
        for (int i = 0; i < n; i++) {
            if (ds.parent[i] == i) cntC++;  // If the node is its own parent, it is the root of a set
        }

        // Step 3: Calculate the number of operations (edges) needed to connect all disjoint sets
        int ans = cntC - 1;  // The number of operations needed is one less than the number of connected components
        if (cntExtras >= ans) return ans;  // If there are enough extra edges, return the answer
        return -1;  // If there aren't enough extra edges, return -1
    }
};

int main() {
    int V = 9;
    vector<vector<int>> edge = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {2, 3}, {4, 5}, {5, 6}, {7, 8}};

    Solution obj;
    int ans = obj.Solve(V, edge);
    cout << "The number of operations needed: " << ans << endl;
    return 0;
}
