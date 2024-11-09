// In this we need to check that from my current node can I go back to the older node if we remove current connected node.
// between new and old . eg: 1 - 2 - 4, so from 4 can we got to 1, if yes then its fine if no then 2 is artulication point

class Solution {
private:
	int timerr = 0;
	void dfs(int node, int parent, vector<int>& timer, vector<int>& low, vector<int>& vis, vector<int> adj[], vector<int>& ap) {
		vis[node] = 1;
		timer[node] = low[node] = timerr;
		timerr ++;
		// for calculating first node
		int child = 0;

		for (auto it : adj[node]) {
			if (it == parent) continue;
			if (vis[it] == 0) {
				dfs(it, node, timer, low, vis, adj, ap);
				low[node] = min(low[it], low[node]);

				// for calculating point which cant be reached
				if (low[it] >= timer[node] && parent != -1) {
					ap[node] = 1;
				}
				child++;
			}
			else {
				low[node] = min(low[node], timer[it]);
			}
		}
		if (child > 1 and parent == -1) {
			ap[node] = 1;
		}
	}

public:
	vector<int> articulationPoints(int n, vector<int>adj[]) {
		// Code heretim
		vector<int> vis(n, 0), timer(n), low(n);
		vector<int> ap(n, 0);
		for (int i = 0; i < n; i++) {
			if (vis[i] == 0) {
				dfs(i, -1, timer, low, vis, adj, ap);
			}
		}
		vector<int> ans;
		for (int i = 0; i < n; i++) {
			if (ap[i] == 1) ans.push_back(i);
		}
		if (ans.empty()) return { -1};
		return ans;
	}
};