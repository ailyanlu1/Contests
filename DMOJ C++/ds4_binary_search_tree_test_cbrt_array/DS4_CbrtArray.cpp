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

#define FACTOR 4

struct Sqrt {
    vector<vector<int>> a;
    vector<int> prefixSZ;
    int n;

    Sqrt() : n(0) {}

    template <typename It>
    Sqrt(It st, It en) : n(en - st) {
        int sqrtn = (int) sqrt(n) * FACTOR;
        for (It i = st; i < en; i += sqrtn) {
            a.emplace_back(i, min(i + sqrtn, en));
            prefixSZ.push_back(0);
        }
        for (int i = 1; i < (int) a.size(); i++) {
            prefixSZ[i] = prefixSZ[i - 1] + (int) a[i - 1].size();
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
        if (n++ == 0) {
            a.emplace_back();
            prefixSZ.push_back(0);
        }
        if (i == (int) a.size()) a[--i].push_back(val);
        else a[i].insert(a[i].begin() + lo, val);
        int sqrtn = (int) sqrt(n) * FACTOR;
        if ((int) a[i].size() > 2 * sqrtn) {
            a.emplace(a.begin() + i + 1, a[i].begin() + sqrtn, a[i].end());
            a[i].resize(sqrtn);
            prefixSZ.push_back(0);
        }
        for (int j = i + 1; j < (int) a.size(); j++) {
            prefixSZ[j] = prefixSZ[j - 1] + (int) a[j - 1].size();
        }
    }

    bool erase(int val) {
        int lo = 0, hi = (int) a.size(), mid;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (a[mid].back() < val) lo = mid + 1;
            else hi = mid;
        }
        if (lo == (int) a.size()) return false;
        int i = lo;
        lo = 0, hi = (int) a[i].size();
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (a[i][mid] < val) lo = mid + 1;
            else hi = mid;
        }
        if (a[i][lo] != val) return false;
        --n;
        a[i].erase(a[i].begin() + lo);
        if (a[i].empty()) {
            a.erase(a.begin() + i);
            prefixSZ.pop_back();
        }
        for (int j = i + 1; j < (int) a.size(); j++) {
            prefixSZ[j] = prefixSZ[j - 1] + (int) a[j - 1].size();
        }
        return true;
    }

    void pop_back() {
        --n;
        a.back().pop_back();
        if (a.back().empty()) {
            a.pop_back();
            prefixSZ.pop_back();
        }
    }

    int back() {
        return a.back().back();
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
        return a[i][lo] == val ? prefixSZ[i] + lo : -1;
    }

    void print() {
        for (int i = 0; i < (int) a.size(); i++) {
            for (int j = 0; j < (int) a[i].size(); j++) {
                cout << a[i][j] << sp;
            }
        }
    }
};

#define MAXN 100005

int N, M, A[MAXN];

vector<Sqrt*> a;
vector<int> prefixSZ;
int n;

void init() {
    n = N;
    int cbrtnsq = (int) cbrt(n) * cbrt(n) * FACTOR;
    for (int i = 0; i < n; i += cbrtnsq) {
        a.emplace_back(new Sqrt(A + i, A + min(i + cbrtnsq, n)));
        prefixSZ.push_back(0);
    }
    for (int i = 1; i < (int) a.size(); i++) {
        prefixSZ[i] = prefixSZ[i - 1] + (int) a[i - 1]->n;
    }
}

void insert(int val) {
    int lo = 0, hi = (int) a.size(), mid;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (val < a[mid]->back()) hi = mid;
        else lo = mid + 1;
    }
    if (n++ == 0) {
        a.push_back(new Sqrt());
        prefixSZ.push_back(0);
    }
    if (lo == (int) a.size()) a[--lo]->insert(val);
    else a[lo]->insert(val);
    int cbrtnsq = (int) cbrt(n) * cbrt(n) * FACTOR;
    if (a[lo]->n > 2 * cbrtnsq) {
        vector<int> b;
        while (a[lo]->n > cbrtnsq) {
            b.push_back(a[lo]->back());
            a[lo]->pop_back();
        }
        reverse(b.begin(), b.end());
        a.insert(a.begin() + lo + 1, new Sqrt(b.begin(), b.end()));
        prefixSZ.push_back(0);
    }
    for (int j = lo + 1; j < (int) a.size(); j++) {
        prefixSZ[j] = prefixSZ[j - 1] + (int) a[j - 1]->n;
    }
}

void erase(int val) {
    int lo = 0, hi = (int) a.size(), mid;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (a[mid]->back() < val) lo = mid + 1;
        else hi = mid;
    }
    if (lo == (int) a.size()) return;
    if (!a[lo]->erase(val)) return;
    --n;
    if (a[lo]->n == 0) {
        delete a[lo];
        a.erase(a.begin() + lo);
        prefixSZ.pop_back();
    }
    for (int j = lo + 1; j < (int) a.size(); j++) {
        prefixSZ[j] = prefixSZ[j - 1] + (int) a[j - 1]->n;
    }
}

int at(int k) {
    int lo = 0, hi = ((int) a.size()) - 1, mid;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        if (k < prefixSZ[mid]) hi = mid - 1;
        else lo = mid + 1;
    }
    return a[hi]->at(k - prefixSZ[hi]);
}

int getRank(int val) {
    int lo = 0, hi = (int) a.size(), mid;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (a[mid]->back() < val) lo = mid + 1;
        else hi = mid;
    }
    if (lo == (int) a.size()) return -1;
    int r = a[lo]->getRank(val);
    return r == -1 ? -1 : prefixSZ[lo] + r;
}

void print() {
    for (int i = 0; i < (int) a.size(); i++) {
        a[i]->print();
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
