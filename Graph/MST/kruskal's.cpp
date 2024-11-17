#include <bits/stdc++.h>
using namespace std;

/*
    Kruskal's Algorithm to find Minimum Spanning Tree (MST) and construct the MST graph.
    
    The algorithm works by:
    1. Sorting all the edges in the graph based on their weights.
    2. Using a Disjoint Set (Union-Find) data structure to ensure that no cycles are formed while constructing the MST.
    3. The edges that connect two different components (sets) are added to the MST.
    
    Steps:
    1. Convert the adjacency list to an edge list (pairs of nodes with weights).
    2. Sort the edges based on their weights.
    3. Initialize the Disjoint Set (Union-Find) to keep track of connected components.
    4. Iterate over the edges:
       - If the two nodes of the edge are in different components, include the edge in the MST.
       - Merge the two components using Union operation.
    5. Track the sum of the weights of the edges in the MST.
    6. Construct the MST graph by adding edges that were included in the MST.
    
    Time Complexity:
    - Sorting the edges: **O(E log E)**, where E is the number of edges.
    - Union-Find operations: **O(α(V))** for each union/find operation, where α is the inverse Ackermann function.
    - Overall Time Complexity: **O(E log E)**.

    Space Complexity:
    - **O(V + E)**: The space complexity is dominated by the adjacency list (O(V + E)) and the Disjoint Set structure (O(V)).

*/

class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    // Find operation with path compression
    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Union operation by rank
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    // Union operation by size
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree and construct the MST graph
    int spanningTree(int V, vector<vector<int>> adj[], vector<vector<int>>& mstGraph) {
        // Step 1: Convert the adjacency list into an edge list
        vector<pair<int, pair<int, int>>> edges;  // {weight, {node1, node2}}

        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                int adjNode = it[0];  // Adjacent node
                int wt = it[1];       // Weight of the edge
                int node = i;         // Current node
                
                // To avoid adding the same edge twice (since the graph is undirected)
                if (node < adjNode) {
                    edges.push_back({wt, {node, adjNode}});
                }
            }
        }

        // Step 2: Initialize Disjoint Set for Kruskal's Algorithm
        DisjointSet ds(V);

        // Step 3: Sort the edges by weight in ascending order
        sort(edges.begin(), edges.end());  

        int mstWt = 0;  // To keep track of the MST weight

        // Step 4: Iterate over the edges and select edges to form the MST
        for (auto it : edges) {
            int wt = it.first;
            int u = it.second.first;
            int v = it.second.second;

            // If the nodes are in different components, include this edge in the MST
            if (ds.findUPar(u) != ds.findUPar(v)) {
                mstWt += wt;
                ds.unionBySize(u, v);

                // Add the edge to the MST graph (undirected graph, add both directions)
                mstGraph[u].push_back(v);
                mstGraph[v].push_back(u);
            }
        }

        return mstWt;  // Return the sum of weights of the MST
    }
};

// Function to print the adjacency list of a graph
void printGraph(int V, vector<vector<int>>& graph) {
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
    vector<vector<int>> edges = {
        {0, 1, 2}, {0, 2, 1}, {1, 2, 1},
        {2, 3, 2}, {3, 4, 1}, {4, 2, 2}
    };
    vector<vector<int>> adj[V];  // Adjacency list of the graph
    
    // Step 1: Convert the edge list into an adjacency list
    for (auto it : edges) {
        vector<int> tmp(2);
        tmp[0] = it[1];  // Adjacent node
        tmp[1] = it[2];  // Weight
        adj[it[0]].push_back(tmp);

        tmp[0] = it[0];  // Reverse direction for undirected graph
        tmp[1] = it[2];  // Weight
        adj[it[1]].push_back(tmp);
    }

    // Step 2: Create the MST graph using Kruskal's Algorithm
    Solution obj;
    vector<vector<int>> mstGraph(V);  // Initialize MST adjacency list
    int mstWt = obj.spanningTree(V, adj, mstGraph);  // Get MST and weight

    // Output the result
    cout << "The sum of all the edge weights of the MST: " << mstWt << endl;

    // Step 3: Print the MST graph
    cout << "MST Graph (Adjacency List):" << endl;
    printGraph(V, mstGraph);

    return 0;
}
