class Solution {
private:
	int timer = 0;
	void dfs(int node, int parent, vector<int>adj[], vector<int> &vis, vector<int> &low, vector<int> &time, vector<vector<int>> &bridge) {
		vis[node] = 1;
		low[node] = time[node] = timer;
		timer++;

		for (auto it : adj[node]) {
			if (it == parent) continue;
			if (vis[it] == 0) {
				dfs(it, node, adj, vis, low, time, bridge);
				low[node] = min(low[it], low[node]);

				// check it the node has low timer
				if (low[it] > time[node]) {
					bridge.push_back({it, node});
				}
			}
			else {
				low[node] = min(low[it], low[node]);
			}
		}


	}

public:
	vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {

		vector<int> adj[n];
		for (auto it : connections) {
			adj[it[0]].push_back(it[1]);
			adj[it[1]].push_back(it[0]);
		}

		vector<int> vis(n, 0), time(n), low(n);
		vector<vector<int>> bridge;
		dfs(0, -1, adj, vis, low, time, bridge);
		return bridge;

	}
};