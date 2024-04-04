#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;


void generateCombinations(const vector<int>& arr, int start, int len, vector<int>& combination, vector<vector<int>>& result) {
    if (len == 0) {
        result.push_back(combination);
        return;
    }

    for (int i = start; i <= arr.size() - len; ++i) {
        combination.push_back(arr[i]);
        generateCombinations(arr, i + 1, len - 1, combination, result);
        combination.pop_back();
    }
}


vector<vector<int>> allCombinations(const vector<int>& arr, int i) {
    vector<vector<int>> result;
    vector<int> combination;
    generateCombinations(arr, 0, i, combination, result);
    return result;
}

void dfs(int node, vector<int> adj[], vector<int>& vis) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        if (vis[it] == 0)
            dfs(it, adj, vis);
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> b(k); 
        for (int i = 0; i < k; i++) {
            cin >> b[i]; 
            b[i]--; 
        }
        vector<int> adj[n];
        for (int i = 1; i < n; i++) {
            int a, b;
            cin >> a >> b;
            adj[a - 1].push_back(b - 1);
            adj[b - 1].push_back(a - 1);
        }

        for (int i = 1; i <= k; ++i) { 
            vector<vector<int>> combinations = allCombinations(b, i);
            int cnt = 0;
            for (const auto& comb : combinations) {
                vector<int> vis(n, 0);
                for (int node : comb)
                    vis[node] = 1;

                for (int j = 0; j < n; j++) {
                    if (vis[j] == 0) {
                        dfs(j, adj, vis);
                        cnt++;
                    }
                }
            }
            
            // long long R = 1LL * cnt * (k - i + 1) % MOD;
            // cout << R << endl;
        }
    }
    return 0;
}
