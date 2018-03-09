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

#define MAXN 100005

int N, M, A[MAXN];
vector<vector<int>> a;
int n;

void init() {
    n = N;
    int sqrtn = (int) sqrt(n);
    for (int i = n; i > 0; i -= sqrtn) {
        a.push_back(vector<int>(A + i - min(i, sqrtn), A + i));
    }
    reverse(a.begin(), a.end());
}

void insert(int k, int val) {
    if (n++ == 0) a.push_back({});
    int i;
    for (i = 0; i < (int) a.size() && k >= (int) a[i].size(); k -= (int) a[i++].size());
    if (i == (int) a.size()) a[--i].push_back(val);
    else a[i].insert(a[i].begin() + k, val);
    int sqrtn = (int) sqrt(n);
    if ((int) a[i].size() > 2 * sqrtn) {
        vector<int> y(a[i].begin() + sqrtn, a[i].end());
        a[i].resize(sqrtn);
        a.insert(a.begin() + i + 1, y);
    }
}

void erase(int k) {
    --n;
    int i;
    for (i = 0; k >= (int) a[i].size(); k -= (int) a[i++].size());
    a[i].erase(a[i].begin() + k);
    if (a[i].empty()) a.erase(a.begin() + i);
}

int at(int k) {
    int i;
    for (i = 0; k >= (int) a[i].size(); k -= (int) a[i++].size());
    return a[i][k];
}

pair<int, int> lower_bound(int val) {
    int i, j, k;
    for (i = 0, k = 0; i < (int) a.size() && a[i].back() < val; k += a[i++].size());
    if (i == (int) a.size()) return {n, 0};
    for (j = 0; a[i][j] < val; j++, k++);
    return {k, a[i][j]};
}

pair<int, int> upper_bound(int val) {
    int i, j, k;
    for (i = 0, k = 0; i < (int) a.size() && a[i].back() <= val; k += a[i++].size());
    if (i == (int) a.size()) return {n, 0};
    for (j = 0; a[i][j] <= val; j++, k++);
    return {k, a[i][j]};
}

void print() {
    for (int i = 0; i < (int) a.size(); i++) {
        for (int j = 0; j < (int) a[i].size(); j++) {
            cout << a[i][j] << sp;
        }
    }
    cout << nl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    FOR(i, N) cin >> A[i];
    sort(A, A + N);
    init();
    int lastAns = 0;
    FOR(i, M) {
        char op;
        int x;
        cin >> op >> x;
        x = x ^ lastAns;
        if (op == 'I') {
            insert(upper_bound(x).f, x);
        } else if (op == 'R') {
            pair<int, int> k = lower_bound(x);
            if (k.s == x) erase(k.f);
        } else if (op == 'S') {
            lastAns = at(x - 1);
            cout << lastAns << nl;
        } else if (op == 'L') {
            pair<int, int> k = lower_bound(x);
            lastAns = k.s == x ? k.f + 1 : -1;
            cout << lastAns << nl;
        } else {
            i--;
        }
    }
    print();
    return 0;
}
