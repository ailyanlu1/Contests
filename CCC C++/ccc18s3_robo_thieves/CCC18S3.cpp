#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl "\n"

#define ll long long
#define ld long double
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXNM 105
#define pii pair<int, int>

int N, M;
char G[MAXNM][MAXNM];
int dist[MAXNM][MAXNM], dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool vis[MAXNM][MAXNM];
pii S;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    string str;
    FOR(i, N) {
        cin >> str;
        FOR(j, M) {
            G[i][j] = str[j];
            if (G[i][j] == 'S') {
                S = {i, j};
                G[i][j] = '.';
            }
            dist[i][j] = -1;
            vis[i][j] = false;
        }
    }
    FOR(i, N) {
        FOR(j, M) {
            if (G[i][j] == 'C') {
                For(k, i + 1, N) {
                    if (G[k][j] == 'W') break;
                    if (G[k][j] == '.') {
                        G[k][j] = 'X';
                        vis[k][j] = true;
                    }
                }
                Rev(k, i - 1, -1) {
                    if (G[k][j] == 'W') break;
                    if (G[k][j] == '.') {
                        G[k][j] = 'X';
                        vis[k][j] = true;
                    }
                }
                For(k, j + 1, M) {
                    if (G[i][k] == 'W') break;
                    if (G[i][k] == '.') {
                        G[i][k] = 'X';
                        vis[i][k] = true;
                    }
                }
                Rev(k, j - 1, -1) {
                    if (G[i][k] == 'W') break;
                    if (G[i][k] == '.') {
                        G[i][k] = 'X';
                        vis[i][k] = true;
                    }
                }
                vis[i][j] = true;
            } else if (G[i][j] == 'W') {
                vis[i][j] = true;
            }
        }
    }
    queue<pii> q;
    dist[S.f][S.s] = 0;
    vis[S.f][S.s] = true;
    q.push(S);
    uset<pii, pair_hash<int, int>> vis2;
    while (!q.empty()) {
        pii cur = q.front();
        q.pop();
        char c = G[cur.f][cur.s];
        if (c == '.') {
            FOR(i, 4) {
                pii nxt = {cur.f + dir[i][0], cur.s + dir[i][1]};
                bool loop = false;
                vis2.clear();
                while (G[nxt.f][nxt.s] != '.') {
                    if (vis2.count(nxt)) {
                        loop = true;
                        break;
                    }
                    vis2.insert(nxt);
                    if (G[nxt.f][nxt.s] == 'U') nxt.f--;
                    else if (G[nxt.f][nxt.s] == 'D') nxt.f++;
                    else if (G[nxt.f][nxt.s] == 'L') nxt.s--;
                    else if (G[nxt.f][nxt.s] == 'R') nxt.s++;
                }
                if (!vis[nxt.f][nxt.s] && !loop) {
                    dist[nxt.f][nxt.s] = dist[cur.f][cur.s] + 1;
                    vis[nxt.f][nxt.s] = true;
                    q.push(nxt);
                }
            }
        }
    }
    G[S.f][S.s] = 'S';
    FOR(i, N) FOR(j, M) if (G[i][j] == '.' || G[i][j] == 'X') cout << dist[i][j] << nl;
    return 0;
}
