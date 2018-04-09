// http://codeforces.com/contest/948/problem/A
#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define all(a) (a).begin(), (a).end()
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pill pair<int, ll>
#define plli pair<ll, int>
#define pdd pair<double, double>
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

char grid[505][505];
int R, C;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> R >> C;
    string line;
    FOR(i, R + 2) FOR(j, C + 2) grid[i][j] = '.';
    For(i, 1, R + 1) {
        cin >> line;
        For(j, 1, C + 1) {
            grid[i][j] = line[j - 1] == '.' ? 'D' : line[j - 1];
        }
    }
    For(i, 1, R + 1) {
        For(j, 1, C + 1) {
            if (grid[i][j] == 'S') {
                if (grid[i][j + 1] == 'W' || grid[i][j - 1] == 'W' || grid[i + 1][j] == 'W' || grid[i - 1][j] == 'W') {
                    cout << "No" << nl;
                    return 0;
                }
            }
        }
    }
    cout << "Yes" << nl;
    For(i, 1, R + 1) {
        For(j, 1, C + 1) {
            cout << grid[i][j];
        }
        cout << nl;
    }
    return 0;
}
