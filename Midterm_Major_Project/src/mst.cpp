#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct Edge {
    int u = 0;
    int v = 0;
    int w = 0;
};

class DisjointSet {
public:
    explicit DisjointSet(int n) : parent(n + 1), rank(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA == rootB) {
            return false;
        }
        if (rank[rootA] < rank[rootB]) {
            swap(rootA, rootB);
        }
        parent[rootB] = rootA;
        if (rank[rootA] == rank[rootB]) {
            ++rank[rootA];
        }
        return true;
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    int m = 0;
    if (!(cin >> n >> m)) {
        cerr << "Expected input format: n m followed by m edges u v w\n";
        return 1;
    }
    if (n <= 0 || m < 0) {
        cerr << "Invalid graph size\n";
        return 1;
    }

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        if (edges[i].u < 1 || edges[i].u > n || edges[i].v < 1 || edges[i].v > n || edges[i].w < 0) {
            cerr << "Invalid edge at line " << (i + 1) << '\n';
            return 1;
        }
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        if (a.w != b.w) {
            return a.w < b.w;
        }
        if (a.u != b.u) {
            return a.u < b.u;
        }
        return a.v < b.v;
    });

    DisjointSet dsu(n);
    vector<Edge> selected;
    long long totalCost = 0;

    for (const Edge& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            selected.push_back(edge);
            totalCost += edge.w;
            if (static_cast<int>(selected.size()) == n - 1) {
                break;
            }
        }
    }

    if (static_cast<int>(selected.size()) != n - 1) {
        cerr << "Graph is disconnected; no spanning tree exists\n";
        return 2;
    }

    cout << "Minimum Spanning Tree by Kruskal\n";
    cout << "Buildings: " << n << '\n';
    cout << "Total cost: " << totalCost << '\n';
    cout << "Selected edges: " << selected.size() << '\n';
    for (const Edge& edge : selected) {
        cout << edge.u << ' ' << edge.v << ' ' << edge.w << '\n';
    }

    return 0;
}
