#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define MAXN 12
#define MAXM 1000005

int N;
bool vis[MAXM];
int dist[MAXM];
ll M, s0, A[MAXN], B[MAXN];
queue<int> q;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> M >> N >> s0;
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i];
        A[i] %= M;
        B[i] %= M;
    }
    q.push(s0);
    dist[s0] = 0;
    vis[s0] = true;
    while (!q.empty()) {
        int s = q.front();
        q.pop();
        if (s == 0) {
            cout << dist[s] << "\n";
            return 0;
        }
        for (int i = 0; i < N; i++) {
            int t = (s * A[i] + B[i]) % M;
            if (vis[t]) continue;
            q.push(t);
            vis[t] = true;
            dist[t] = dist[s] + 1;
        }
    }
    cout << -1 << "\n";
    return 0;
}
