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
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl "\n"

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

#define MAXN 200005

int N, Q, M, A, K, I;
string S;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    if (Q <= 12) {
        FOR(i, N) S.pb('Z');
        int t, l, r;
        char c;
        FOR(q, Q) {
            cin >> t;
            if (t == 1) {
                cin >> l >> r >> c;
                l--; r--;
                For(i, l, r + 1) S[i] = c;
            } else if (t == 2) {
                cin >> l >> r;
                l--; r--;
                M = A = K = I = 0;
                For(i, l, r + 1) {
                    if (S[i] == 'M') M++;
                    else if (S[i] == 'A' && M > 0) {
                        M--;
                        A++;
                    } else if (S[i] == 'K' && A > 0) {
                        A--;
                        K++;
                    } else if (S[i] == 'I' && K > 0) {
                        K--;
                        I++;
                    }
                }
                cout << I << nl;
            } else {
                q--;
            }
        }
    }
    return 0;
}
