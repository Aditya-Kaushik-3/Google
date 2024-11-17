#include <vector>
#include <set>
#include <algorithm>

using namespace std;

/*
    **Distinct Islands Problem**

    This implementation counts the number of distinct islands in a 2D boolean matrix. A group of connected `1`s forms an island, and two islands are considered the same if one can be obtained by rotating or reflecting the other.

    **Steps:**
    1. We iterate through each cell in the grid.
    2. If a `1` (land) is found and the cell is unvisited, we perform a Depth-First Search (DFS) to explore the entire island.
    3. The relative coordinates of each cell in the island are stored, and the island's shape is normalized to handle different positions or orientations.
    4. The normalized island shape is added to a set to ensure that only distinct islands are counted.
    5. After all the cells are processed, the number of distinct islands is returned.

    **Time Complexity:**
    - **DFS traversal:** O(n * m), where `n` is the number of rows and `m` is the number of columns in the grid. Each cell is visited once.
    - **Normalization (Sorting):** O(k log k), where `k` is the number of cells in the island. Sorting the island's coordinates takes time proportional to the number of cells in the island.
    - **Set operations (Insertion):** Insertion into the set takes O(k log k), where `k` is the size of the island.
    - Overall time complexity is O(n * m * k log k), but in practice, the largest island `k` is usually much smaller than `n * m`, so this should be efficient.

    **Space Complexity:**
    - **Visited matrix:** O(n * m), to track whether each cell has been visited.
    - **Island storage:** O(k), where `k` is the number of cells in the largest island. Each island's coordinates are stored.
    - **Set to store unique islands:** In the worst case, O(n * m) if every cell in the grid is part of a distinct island.
    - Overall space complexity: O(n * m).

*/

class Solution {
public:
    // Function to count the number of distinct islands
    int countDistinctIslands(vector<vector<int>>& grid) {
        int n = grid.size();  // Number of rows in the grid
        int m = grid[0].size();  // Number of columns in the grid
        set<vector<pair<int, int>>> uniqueIslands;  // Set to store distinct island shapes
        
        // 2D array to mark visited cells
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        
        // Iterate through the grid and perform DFS on each unvisited land cell
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // If the cell is land (1) and not visited yet
                if (grid[i][j] == 1 && !visited[i][j]) {
                    vector<pair<int, int>> island;  // Vector to store the relative coordinates of the island
                    // Perform DFS to explore the entire island starting from (i, j)
                    dfs(grid, visited, i, j, i, j, island);
                    // Normalize the island's shape to handle different positions
                    normalize(island);
                    // Insert the normalized shape into the set of unique islands
                    uniqueIslands.insert(island);
                }
            }
        }
        
        // Return the number of unique islands
        return uniqueIslands.size();
    }
    
private:
    // Helper function to perform DFS and capture the island's relative coordinates
    void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int i, int j, int base_i, int base_j, vector<pair<int, int>>& island) {
        int n = grid.size();  // Number of rows
        int m = grid[0].size();  // Number of columns
        
        // Base case: out of bounds or the cell is water (0) or already visited
        if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j] == 0 || visited[i][j]) {
            return;
        }
        
        // Mark the cell as visited
        visited[i][j] = true;
        // Store the relative position of the current cell with respect to the starting point of the island
        island.push_back({i - base_i, j - base_j});
        
        // Explore the four directions (down, up, right, left)
        dfs(grid, visited, i + 1, j, base_i, base_j, island);
        dfs(grid, visited, i - 1, j, base_i, base_j, island);
        dfs(grid, visited, i, j + 1, base_i, base_j, island);
        dfs(grid, visited, i, j - 1, base_i, base_j, island);
    }
    
    // Helper function to normalize the island's shape
    void normalize(vector<pair<int, int>>& island) {
        // Sort the island coordinates to make the shape consistent
        sort(island.begin(), island.end());
        
        // Get the base coordinates (top-left corner) of the island
        int base_i = island[0].first;
        int base_j = island[0].second;
        
        // Normalize by shifting all coordinates relative to the base
        for (auto& p : island) {
            p.first -= base_i;
            p.second -= base_j;
        }
    }
};
