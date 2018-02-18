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

#define MAXS 500005

string S, T;
int ans[MAXS], LCP[MAXS];
bool match[MAXS];

void pre() {
    FOR(i, sz(T) + 1) LCP[i] = 0;
    LCP[0] = -1;
    for (int i = 0, j = -1; i < sz(T); i++, j++, LCP[i] = j) {
        while (j >= 0 && T[i] != T[j]) {
            j = LCP[j];
        }
    }
}

void search() {
    FOR(i, sz(S)) match[i] = false;
    for (int i = 0, j = 0; i < sz(S); i++, j++) {
        while (j >= 0 && S[i] != T[j]) {
            j = LCP[j];
        }
        if (j == sz(T) - 1) {
            match[i - j] = true;
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> S;
    FOR(i, sz(S)) ans[i] = 0;
    if (sz(S) <= 50005) {
        For(k, 1, sz(S) + 1) {
            T.pb(S[k - 1]);
            pre();
            search();
            For(i, k - 1, sz(S) - k + 1) if (match[i - k + 1] && match[i]) ans[i] = k;
        }
    } else {
        FOR(i, sz(S)) ans[i] = min(i, sz(S) - i - 1) + 1;
    }
    FOR(i, sz(S)) cout << ans[i] << " \n"[i == sz(S) - 1];
    return 0;
}
