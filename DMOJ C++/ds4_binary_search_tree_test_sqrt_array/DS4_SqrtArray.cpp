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
vector<int> prefixSZ;
int n;

void init() {
    n = N;
    int sqrtn = (int) sqrt(n);
    for (int i = n; i > 0; i -= sqrtn) {
        a.push_back(vector<int>(A + i - min(i, sqrtn), A + i));
        prefixSZ.push_back(0);
    }
    reverse(a.begin(), a.end());
    for (int i = 1; i < (int) a.size(); i++) {
        prefixSZ[i] = prefixSZ[i - 1] + (int) a[i - 1].size();
    }
}

void insert(int k, int val) {
    if (n++ == 0) {
        a.push_back({});
        prefixSZ.push_back(0);
    }
    int lo = 0, hi = (int) (a.size()) - 1, mid;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        if (k < prefixSZ[mid]) hi = mid - 1;
        else lo = mid + 1;
    }
    k -= prefixSZ[hi];
    if (hi == -1) a[hi += (int) a.size()].push_back(val);
    else a[hi].insert(a[hi].begin() + k, val);
    int sqrtn = (int) sqrt(n);
    if ((int) a[hi].size() > 2 * sqrtn) {
        vector<int> y(a[hi].begin() + sqrtn, a[hi].end());
        a[hi].resize(sqrtn);
        a.insert(a.begin() + hi + 1, y);
        prefixSZ.push_back(0);
    }
    for (int i = 1; i < (int) a.size(); i++) {
        prefixSZ[i] = prefixSZ[i - 1] + (int) a[i - 1].size();
    }
}

void erase(int k) {
    --n;
    int lo = 0, hi = (int) (a.size()) - 1, mid;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        if (k < prefixSZ[mid]) hi = mid - 1;
        else lo = mid + 1;
    }
    k -= prefixSZ[hi];
    a[hi].erase(a[hi].begin() + k);
    if (a[hi].empty()) {
        a.erase(a.begin() + hi);
        prefixSZ.pop_back();
    }
    for (int i = 1; i < (int) a.size(); i++) {
        prefixSZ[i] = prefixSZ[i - 1] + (int) a[i - 1].size();
    }
}

int at(int k) {
    int lo = 0, hi = (int) (a.size()) - 1, mid;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        if (k < prefixSZ[mid]) hi = mid - 1;
        else lo = mid + 1;
    }
    return a[hi][k - prefixSZ[hi]];
}

pair<int, int> lower_bound(int val) {
    int lo = 0, hi = (int) a.size(), mid;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (a[mid].back() < val) lo = mid + 1;
        else hi = mid;
    }
    if (lo == (int) a.size()) return {n, 0};
    int i = lo;
    lo = 0, hi = (int) a[i].size();
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (a[i][mid] < val) lo = mid + 1;
        else hi = mid;
    }
    return {prefixSZ[i] + lo, a[i][lo]};
}

pair<int, int> upper_bound(int val) {
    int lo = 0, hi = (int) a.size(), mid;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (val < a[mid].back()) hi = mid;
        else lo = mid + 1;
    }
    if (lo == (int) a.size()) return {n, 0};
    int i = lo;
    lo = 0, hi = (int) a[i].size();
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (val < a[i][mid]) hi = mid;
        else lo = mid + 1;
    }
    return {prefixSZ[i] + lo, a[i][lo]};
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
