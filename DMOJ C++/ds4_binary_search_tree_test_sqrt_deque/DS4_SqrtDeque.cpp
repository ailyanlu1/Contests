#include <bits/stdc++.h>
using namespace std;

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

#define MAXN 100005

int N, M, A[MAXN];
int n;
int blockSize = 2048;
deque<deque<int>> a;

void init() {
    n = N;
    for (int i = 0; i < n; i += blockSize) {
        a.emplace_back(A + i, A + min(i + blockSize, n));
    }
}

void insert(int val) {
    int lo = 0, hi = (int) a.size(), mid;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (val < a[mid].back()) hi = mid;
        else lo = mid + 1;
    }
    int i = lo;
    if (lo != (int) a.size()) {
        lo = 0, hi = (int) a[i].size();
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (val < a[i][mid]) hi = mid;
            else lo = mid + 1;
        }
    }
    if (n++ == 0) a.emplace_back();
    if (i == (int) a.size()) a[--i].push_back(val);
    else a[i].insert(a[i].begin() + lo, val);
    if (i < (int) a.size() / 2) {
        for (int j = i - 1; j >= 0; j--) {
            a[j].push_back(a[j + 1].front());
            a[j + 1].pop_front();
        }
        if ((int) a.front().size() > blockSize) {
            a.emplace_front();
            a.front().push_back(a[1].front());
            a[1].pop_front();
        }
    } else {
        for (int j = i + 1; j < (int) a.size(); j++) {
            a[j].push_front(a[j - 1].back());
            a[j - 1].pop_back();
        }
        if ((int) a.back().size() > blockSize) {
            a.emplace_back();
            a.back().push_front(a[((int) a.size()) - 2].back());
            a[((int) a.size()) - 2].pop_back();
        }
    }
}

void erase(int val) {
    int lo = 0, hi = (int) a.size(), mid;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (a[mid].back() < val) lo = mid + 1;
        else hi = mid;
    }
    if (lo == (int) a.size()) return;
    int i = lo;
    lo = 0, hi = (int) a[i].size();
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (a[i][mid] < val) lo = mid + 1;
        else hi = mid;
    }
    if (a[i][lo] != val) return;
    --n;
    a[i].erase(a[i].begin() + lo);
    if (i < (int) a.size() / 2) {
        for (int j = i - 1; j >= 0; j--) {
            a[j + 1].push_front(a[j].back());
            a[j].pop_back();
        }
        if (a.front().empty()) a.pop_front();
    } else {
        for (int j = i + 1; j < (int) a.size(); j++) {
            a[j - 1].push_back(a[j].front());
            a[j].pop_front();
        }
        if (a.back().empty()) a.pop_back();
    }
}

int at(int k) {
    if (k < (int) a[0].size()) return a[0][k];
    k -= (int) a[0].size();
    return a[1 + k / blockSize][k % blockSize];
}

int getRank(int val) {
    int lo = 0, hi = (int) a.size(), mid;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (a[mid].back() < val) lo = mid + 1;
        else hi = mid;
    }
    if (lo == (int) a.size()) return -1;
    int i = lo;
    lo = 0, hi = (int) a[i].size();
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (a[i][mid] < val) lo = mid + 1;
        else hi = mid;
    }
    if (a[i][lo] != val) return -1;
    if (i == 0) return lo;
    return (int) a[0].size() + (i - 1) * blockSize + lo;
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
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
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
            insert(x);
        } else if (op == 'R') {
            erase(x);
        } else if (op == 'S') {
            lastAns = at(x - 1);
            cout << lastAns << nl;
        } else if (op == 'L') {
            int k = getRank(x);
            lastAns = k == -1 ? -1 : k + 1;
            cout << lastAns << nl;
        } else {
            i--;
        }
    }
    print();
    return 0;
}
