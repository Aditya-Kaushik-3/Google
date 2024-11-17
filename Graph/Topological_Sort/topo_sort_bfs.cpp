#include <bits/stdc++.h>
using namespace std;

/*
    **Topological Sort Using Kahn's Algorithm (BFS-based)**

    This implementation finds a topological order of the vertices in a Directed Acyclic Graph (DAG) using Kahn's Algorithm, 
    which is based on Breadth-First Search (BFS). The algorithm uses the concept of **indegree** (number of incoming edges) 
    to perform the sorting.

    **Steps:**
    1. Calculate the **indegree** for each node. The indegree of a node is the number of edges directed towards it.
    2. Initialize a **queue** and push all nodes with indegree 0 (i.e., nodes with no incoming edges) into the queue.
    3. Process each node from the queue:
       - Remove the node from the queue and add it to the topological order.
       - For each of its neighbors, reduce their indegree by 1 (because one incoming edge has been processed).
       - If any neighbor's indegree becomes 0, add it to the queue.
    4. Repeat this process until all nodes are processed, resulting in a valid topological order.

    **Time Complexity:**
    - **Indegree Calculation:** O(V + E), where V is the number of vertices and E is the number of edges. We visit each node and each edge once.
    - **BFS (Queue Processing):** O(V + E). Each node and each edge is processed once during BFS.
    - Overall time complexity: **O(V + E)**.

    **Space Complexity:**
    - **Indegree Array:** O(V), to store the indegree of each node.
    - **Queue:** O(V), to store nodes in the queue during the BFS process.
    - **Topological Order Array:** O(V), to store the result.
    - Overall space complexity: **O(V)** (excluding the input graph).

*/

class Solution {
public:
    // Function to return the list containing vertices in Topological order
    vector<int> topoSort(int V, vector<int> adj[]) {
        int indegree[V] = {0};  // Array to store the indegree of each vertex
        
        // Step 1: Calculate the indegree for each node
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                indegree[it]++;  // Increment indegree of adjacent node
            }
        }

        // Step 2: Initialize the queue with nodes having indegree 0
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);  // Add nodes with indegree 0 to the queue
            }
        }

        vector<int> topo;  // Vector to store the topological order

        // Step 3: Process nodes from the queue
        while (!q.empty()) {
            int node = q.front();  // Get the front element from the queue
            q.pop();
            topo.push_back(node);  // Add the node to the topological order

            // Step 4: Update indegree of adjacent nodes and add to queue if indegree becomes 0
            for (auto it : adj[node]) {
                indegree[it]--;  // Decrease the indegree of the adjacent node
                if (indegree[it] == 0) {
                    q.push(it);  // If indegree becomes 0, add it to the queue
                }
            }
        }

        return topo;  // Return the topological order
    }
};
