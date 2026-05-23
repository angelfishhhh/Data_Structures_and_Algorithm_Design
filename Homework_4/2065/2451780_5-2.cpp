/*
算法基本思想：
1. 图是无向带权图，先用邻接表存储每条边及其耗时。
2. 路径必须从节点 0 出发，因此 DFS 起点固定为 0。
3. DFS 过程中维护：
   - 当前所在节点 u；
   - 当前已经花费的时间 time；
   - 当前路径价值 score；
   - 每个节点的访问次数 visited。
4. 当第一次访问某个节点时，才把 values[u] 加入路径价值；
   如果该节点之前已经访问过，则不重复加分。
5. 每次 DFS 到节点 0 时，说明当前路径是一条合法路径，
   用当前路径价值更新答案。
6. 继续向相邻节点搜索，但只有在总时间不超过 maxTime 时才递归。
7. 递归结束后恢复 visited 状态，即完成回溯。
*/

class Solution {
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        int n = values.size();
        vector<vector<pair<int, int>>> graph(n);

        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            int time = e[2];

            graph[u].push_back({v, time});
            graph[v].push_back({u, time});
        }

        vector<int> visited(n, 0);
        visited[0] = 1;

        int ans = values[0];

        dfs(0, 0, values[0], maxTime, values, graph, visited, ans);

        return ans;
    }

private:
    void dfs(
        int u,
        int curTime,
        int curScore,
        int maxTime,
        vector<int>& values,
        vector<vector<pair<int, int>>>& graph,
        vector<int>& visited,
        int& ans
    ) {
        if (u == 0) {
            ans = max(ans, curScore);
        }

        for (auto& [v, cost] : graph[u]) {
            int nextTime = curTime + cost;

            if (nextTime > maxTime) {
                continue;
            }

            bool firstVisit = (visited[v] == 0);

            visited[v]++;

            if (firstVisit) {
                curScore += values[v];
            }

            dfs(v, nextTime, curScore, maxTime, values, graph, visited, ans);

            if (firstVisit) {
                curScore -= values[v];
            }

            visited[v]--;
        }
    }
};