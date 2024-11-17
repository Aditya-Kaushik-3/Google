#include <bits/stdc++.h>
using namespace std;

/*
    **Topological Sort Using DFS**

    This implementation performs a topological sort on a Directed Acyclic Graph (DAG) using Depth First Search (DFS). 
    The goal of topological sorting is to order the nodes such that for every directed edge u -> v, u comes before v in the ordering.

    **Steps:**
    1. Initialize a `visited` vector to keep track of the visited nodes.
    2. Use a DFS function to explore all nodes starting from any unvisited node.
    3. Once a node's descendants are fully processed, push it onto the stack.
    4. After completing DFS for all nodes, the stack contains the nodes in reverse topological order.
    5. Pop nodes from the stack to obtain the topologically sorted order.

    **Time Complexity:**
    - **DFS traversal:** O(V + E), where V is the number of vertices (nodes) and E is the number of edges in the graph.
    - **Popping from the stack to create the result array:** O(V).
    - Overall time complexity: **O(V + E)**.

    **Space Complexity:**
    - **Visited array:** O(V), to store the visited status of each node.
    - **Stack:** O(V), to store the nodes as they are processed.
    - Overall space complexity: **O(V)** (not counting the input graph).

*/

void dfs(int node, vector<int>& vis, stack<int>& st, vector<vector<int>>& adj){
    vis[node] = 1;  // Mark the node as visited
    for (auto it : adj[node]) {  // Explore all adjacent nodes (edges)
        if (!vis[it]) {  // If the adjacent node is not visited, perform DFS
            dfs(it, vis, st, adj);
        }
    }
    st.push(node);  // After all neighbors are processed, push the node onto the stack
}

vector<int> topologicalSort(vector<vector<int>>& adj) {
    int n = adj.size();  // Number of nodes in the graph
    vector<int> vis(n, 0);  // Vector to keep track of visited nodes
    stack<int> st;  // Stack to store nodes in reverse topological order

    // Perform DFS on all unvisited nodes
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {  // If the node is not yet visited, start a DFS
            dfs(i, vis, st, adj);
        }
    }

    // Create the result array to store topologically sorted nodes
    vector<int> ans;
    while (!st.empty()) {  // Pop nodes from the stack to get the topological order
        ans.push_back(st.top());
        st.pop();
    }

    return ans;  // Return the topologically sorted order
}

