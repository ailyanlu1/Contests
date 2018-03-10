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

template <typename T>
struct SqrtArray {
private:
    int n;
    int blockSZ;
    vector<vector<T>> a;
    vector<T> sum;

public:
    SqrtArray(const int n) : n(n) {
        blockSZ = (int) sqrt(n);
        for (int i = n; i > 0; i -= blockSZ) {
            a.push_back(vector<T>(min(i, blockSZ)));
            sum.push_back(0);
        }
    }

    void update(int k, T val) {
        a[k / blockSZ][k % blockSZ] += val;
        sum[k / blockSZ] += val;
    }

    T query(int l, int r) const {
        T ans = 0;
        while (l % blockSZ != 0 && l <= r) {
            ans += a[l / blockSZ][l % blockSZ];
            l++;
        }
        while (l / blockSZ < r / blockSZ) {
            ans += sum[l / blockSZ];
            l += blockSZ;
        }
        while (l <= r) {
            ans += a[l / blockSZ][l % blockSZ];
            l++;
        }
        return ans;
    }
};

#define MAXNV 100005

int N, M, x, y, A[MAXNV];
ll v, oldV;
char op;
SqrtArray<ll> *sum;
SqrtArray<int> *cnt;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    sum = new SqrtArray<ll>(N + 1);
    cnt = new SqrtArray<int>(MAXNV);
    For(i, 1, N + 1) {
        cin >> A[i];
        sum->update(i, A[i]);
        cnt->update(A[i], 1);
    }
    FOR(i, M) {
        cin >> op;
        if (op == 'C') {
            cin >> x >> v;
            sum->update(x, v - A[x]);
            cnt->update(A[x], -1);
            cnt->update(v, 1);
            A[x] = v;
        } else if (op == 'S') {
            cin >> x >> y;
            cout << sum->query(x, y) << nl;
        } else if (op == 'Q') {
            cin >> x;
            cout << cnt->query(1, x) << nl;
        } else {
            i--;
        }
    }
    return 0;
}
