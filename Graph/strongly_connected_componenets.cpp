
// Strongly connected componenets

// Step 1 : Sort all the edges according to compilition and put into some ds
// Step 2 : Reverse the Graph
// Step 3 : Do the DFS

class solution
{
private:
	// First DFS to store finishing order in stack
	void dfs(int node, vector<int> &vis, stack<int> &end, vector<vector<int>> &adj) {
		vis[node] = 1;
		for (auto it : adj[node]) {
			if (vis[it] == 0) {  // Corrected: Check if the adjacent node is unvisited
				dfs(it, vis, end, adj);
			}
		}
		end.push(node);  // Push the node to stack once all of its neighbors are visited
	}

	// Second DFS to explore the transposed graph
	void dfs2(int node, vector<int> &vis, vector<vector<int>> &adjT) {
		vis[node] = 1;
		for (auto it : adjT[node]) {
			if (vis[it] == 0) {  // Corrected: Check if the adjacent node is unvisited
				dfs2(it, vis, adjT);
			}
		}
	}

public:
	// Function to find number of strongly connected components in the graph.
	int kosaraju(int n, vector<vector<int>>& adj) {
		// Step 1: Perform DFS to fill the stack with finishing order
		vector<int> vis(n, 0);
		stack<int> end;
		for (int i = 0; i < n; i++) {
			if (!vis[i]) {
				dfs(i, vis, end, adj);
			}
		}

		// Step 2: Transpose the graph (reverse all edges)
		vector<vector<int>> adjT(n);  // Transposed graph
		for (int i = 0; i < n; i++) {
			for (auto it : adj[i]) {
				adjT[it].push_back(i);  // Reverse the direction of edges
			}
		}

		// Step 3: Perform DFS on the transposed graph using the stack order
		fill(vis.begin(), vis.end(), 0);  // Reset visited array
		int scc = 0;

		// Process nodes in order of finishing times (from the stack)
		while (!end.empty()) {
			int node = end.top();
			end.pop();

			if (!vis[node]) {  // If the node is unvisited, it's a new SCC
				scc++;
				dfs2(node, vis, adjT);
			}
		}

		// For Printing All
		// vector<vector<int>> ssc_data;
		// int scc = 0;

		// // Process nodes in order of finishing times (from the stack)
		// while (!end.empty()) {
		//     int node = end.top();
		//     end.pop();
		//     vector<int> connected;

		//     if (!vis[node]) {  // If the node is unvisited, it's a new SCC
		//         scc++;
		//         dfs2(node, vis, adjT, conneced);
		//         scc_data.push_back(connected);
		//     }
		// }

		return scc;  // Return the number of strongly connected components
	}
};