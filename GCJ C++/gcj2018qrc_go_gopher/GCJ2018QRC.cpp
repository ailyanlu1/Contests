// https://codejam.withgoogle.com/2018/challenges/00000000000000cb/dashboard/0000000000007a30
#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define eb emplace_back
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

#define MAXRC 1005

int T, A;
bool grid[MAXRC][MAXRC];

bool check3(int i, int j) {
    return grid[i][j] && grid[i - 1][j] && grid[i + 1][j];
}

bool check6(int i, int j) {
    return check3(i, j - 1) && check3(i, j);
}

bool check9(int i, int j) {
    return check6(i, j) && check3(i, j + 1);
}

int okay, good, passed, error;

void solve(int t) {
    cin >> A;
    memset(grid, false, sizeof(grid));
    int curI = 2;
    int curJ = 2;
    int cnt = 0;
    while (true) {
        cout << curI << sp << curJ << endl;
        int i, j;
        cin >> i >> j;
        cnt++;
        if (i <= 0 && j <= 0) {
            if (i == -1 && j == -1) error++;
            if (cnt > 800) okay--;
            if (cnt > 600) good--;
            if (cnt > 1000) passed--;
            return;
        }
        grid[i][j] = true;
        if (check9(curI, curJ)) curJ += 3;
        else if (check6(curI, curJ)) curJ += 2;
        else if (check3(curI, curJ - 1)) curJ++;
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    okay = good = passed = T;
    error = 0;
    FOR(i, T) solve(i + 1);
    cerr << "GOOD: " << good << endl;
    cerr << "OKAY: " << okay << endl;
    cerr << "PASSED: " << passed << endl;
    cerr << "ERROR: " << error << endl;
    return 0;
}
