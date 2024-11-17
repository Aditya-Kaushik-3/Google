#include <bits/stdc++.h>
using namespace std;

/*
    Disjoint Set (Union-Find) with Path Compression and Union by Size
    
    The Disjoint Set data structure is used to keep track of a partition of a set into disjoint subsets.
    It supports two primary operations:
    1. **Find**: Determine which subset a particular element is in.
    2. **Union**: Merge two subsets into a single subset.
    
    This implementation uses two optimizations:
    1. **Path Compression**: Optimizes the `find` operation by making nodes in the path point directly to the root.
    2. **Union by Size**: Ensures that smaller sets are merged into larger sets to keep the tree depth minimal.

    Steps:
    1. **Initialization**: Each node is initially its own parent, and each set has a size of 1.
    2. **Find**: To find the root (or representative) of the set to which a node belongs. This operation also uses path compression for optimization.
    3. **Union**: To merge two sets, the smaller set is merged into the larger one (union by size) to ensure the tree remains shallow.

    Time Complexity:
    - The **find** operation with path compression has a time complexity of **O(α(N))**, where α is the inverse Ackermann function. This is almost constant in practice.
    - The **union** operation with union by size takes **O(α(N))** time, as it involves two `find` operations followed by a constant-time merge.
    - Thus, both operations are nearly constant time, **O(α(N))** in practical scenarios, where N is the number of nodes in the disjoint set.

    Space Complexity:
    - We use three arrays: `parent[]`, `size[]`, and optionally `rank[]` (if used). All these arrays are of size **O(N)**.
    - Thus, the space complexity is **O(N)**.

*/

class DisjointSet {
    vector<int> rank, parent, size;  // rank is not used in this code, but it's a common optimization to keep it for future use

public:
    // Constructor: Initializes the parent and size arrays
    DisjointSet(int n) {
        // rank.resize(n + 1, 0);
        parent.resize(n + 1);  // To store parent of each node (1-based index)
        size.resize(n + 1);    // To store size of the set for each node (1-based index)

        // Initially, each node is its own parent, and the size of each set is 1.
        for (int i = 0; i <= n; i++) {
            parent[i] = i;      // Every node is its own parent initially
            size[i] = 1;        // Size of each set is 1 initially (each node is a separate set)
        }
    }

    // Function to find the representative or root of the set that 'node' belongs to
    int findUPar(int node) {
        // Path compression optimization: Recursively find the root and make the path shorter
        if (node == parent[node]) 
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Union by size: Merge the smaller set into the larger one (to keep the tree shallow)
    void unionBySize(int u, int v) {
        // Find the roots of the sets that 'u' and 'v' belong to
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);

        // If they are already in the same set, no need to union
        if (ulp_u == ulp_v) return;

        // Union by size: Attach the smaller tree to the larger one
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;  // Make root of u point to root of v
            size[ulp_v] += size[ulp_u];  // Add the size of u's set to v's set
        } else {
            parent[ulp_v] = ulp_u;  // Make root of v point to root of u
            size[ulp_u] += size[ulp_v];  // Add the size of v's set to u's set
        }

    // void unionByRank(int u, int v) {
    //     int ulp_u = findUPar(u);
    //     int ulp_v = findUPar(v);
    //     if (ulp_u == ulp_v) return;
    //     if (rank[ulp_u] < rank[ulp_v]) {
    //         parent[ulp_u] = ulp_v;
    //     }
    //     else if (rank[ulp_v] < rank[ulp_u]) {
    //         parent[ulp_v] = ulp_u;
    //     }
    //     else {
    //         parent[ulp_v] = ulp_u;
    //         rank[ulp_u]++;
    //     }
    // }

    }
};

int main() {
    // Create a Disjoint Set with 7 nodes (1-based index)
    DisjointSet ds(7);  

    // Union operations: Create connections between different nodes
    ds.unionBySize(1, 2);  // Connect node 1 and 2
    ds.unionBySize(2, 3);  // Connect node 2 and 3
    ds.unionBySize(4, 5);  // Connect node 4 and 5
    ds.unionBySize(6, 7);  // Connect node 6 and 7
    ds.unionBySize(5, 6);  // Connect node 5 and 6

    // Checking if nodes 3 and 7 belong to the same set (before union)
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n";  // If they have the same root, they are in the same set
    } else {
        cout << "Not same\n";  // Otherwise, they are in different sets
    }

    // Perform a union of sets containing nodes 3 and 7
    ds.unionBySize(3, 7);

    // Checking if nodes 3 and 7 belong to the same set (after union)
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n";  // After union, they should be in the same set
    } else {
        cout << "Not same\n";  // This should not happen after the union
    }

    return 0;
}
