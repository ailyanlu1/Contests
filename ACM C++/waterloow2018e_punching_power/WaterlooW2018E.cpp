#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
#define x first
#define y second

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXN 2005

int N;
vector<int> adj[MAXN];
bool color[MAXN], vis[MAXN];
int dist[MAXN], mate[MAXN], cur[MAXN];
unordered_map<pii, int, pair_hash<int, int>> points;

inline bool isMatched(int v) {
    return mate[v] != -1;
}

bool isResidual(int v, int w) {
    if ((mate[v] != w) && color[v]) return true;
    if ((mate[v] == w) && !color[v]) return true;
    return false;
}

bool isLevel(int v, int w) {
    return dist[w] == dist[v] + 1 && isResidual(v, w);
}

bool hasPath() {
    for (int v = 0; v < N; v++) {
        vis[v] = false;
        dist[v] = INT_MAX;
    }
    queue<int> q;
    for (int v = 0; v < N; v++) {
        if (color[v] && !isMatched(v)) {
            q.push(v);
            vis[v] = true;
            dist[v] = 0;
        }
    }
    bool hasPath = false;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int w : adj[v]) {
            if (isResidual(v, w)) {
                if (!vis[w]) {
                    dist[w] = dist[v] + 1;
                    vis[w] = true;
                    if (!isMatched(w)) hasPath = true;
                    if (!hasPath) q.push(w);
                }
            }
        }
    }
    return hasPath;
}

int maxMatch() {
    int cardinality = 0;
    for (int v = 0; v < N; v++) mate[v] = -1;
    while (hasPath()) {
        for (int v = 0; v < N; v++) cur[v] = 0;
        for (int s = 0; s < N; s++) {
            if (isMatched(s) || !color[s]) continue;
            stack<int> path;
            path.push(s);
            while (!path.empty()) {
                int v = path.top();
                if (cur[v] >= (int) adj[v].size()) path.pop();
                else {
                    int w = adj[v][cur[v]++];
                    if (!isLevel(v, w)) continue;
                    path.push(w);
                    if (!isMatched(w)) {
                        while (!path.empty()) {
                            int x = path.top();
                            path.pop();
                            int y = path.top();
                            path.pop();
                            mate[x] = y;
                            mate[y] = x;
                        }
                        cardinality++;
                    }
                }
            }
        }
    }
    return cardinality;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    while (cin >> N) {
        points.clear();
        for (int i = 0; i < N; i++) {
            pii p;
            cin >> p.x >> p.y;
            points[p] = i;
            color[i] = (p.x + p.y) % 2 == 0;
        }
        for (pair<pii, int> p : points) {
            pii up = {p.first.x, p.first.y + 1};
            pii down = {p.first.x, p.first.y - 1};
            pii right = {p.first.x + 1, p.first.y};
            pii left = {p.first.x - 1, p.first.y};
            if (points.count(up)) adj[p.second].push_back(points[up]);
            if (points.count(down)) adj[p.second].push_back(points[down]);
            if (points.count(right)) adj[p.second].push_back(points[right]);
            if (points.count(left)) adj[p.second].push_back(points[left]);
        }
        cout << N - maxMatch() << "\n";
        for (int i = 0; i < N; i++) adj[i].clear();
    }
    return 0;
}
