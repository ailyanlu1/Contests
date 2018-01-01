#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) ((x) << 1)
#define r(x) ((x) << 1 | 1)
#define m(x, y) ((x) + ((y) - (x)) / 2)
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rld(x) scanf("%Lf", &x)
#define rc(x) scanf(" %c", &x)
#define sc(x) do { scanf("%c", &x); } while (isspace(x))
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define set0(a) memset((a), 0, sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define Fill2(a, x, n, m) FOR(_, n) FOR(__, m) (a)[_][__] = (x)
#define Fill3(a, x, n, m, p) FOR(_, n) FOR(__, m) FOR(___, p) (a)[_][__][___] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))
#define sz(a) ((int) (a).size())
#define len(a) ((int) (a).length())

typedef long long ll;
typedef unsigned long long llu;
typedef long double ld;
#define uset unordered_set
#define umap unordered_map
#define pq priority_queue
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef map<ll, ll> mll;
typedef umap<int, int> umii;
typedef umap<int, ll> umill;
typedef umap<ll, int> umlli;
typedef umap<ll, ll> umll;
template<typename T> using minpq = pq<T, vector<T>, greater<T>>;
template<typename T> using maxpq = pq<T, vector<T>, less<T>>;

#define debug(fmt, x) fprintf(stderr, "%d::%s = " fmt, __LINE__, #x, (x)); fflush(stderr)
#define debug2(x) cerr << __LINE__ << "::" << #x << " = " << (x) << '\n' << flush
#define debugva(fmt, ...) fprintf(stderr, "%d::%s = " fmt, __LINE__, #__VA_ARGS__, __VA_ARGS__); fflush(stderr)
#define debugarr(fmt, x, a, b) fprintf(stderr, "%d::%s = {", __LINE__, #x); For(_, a, b) { if (_ != (a)) { fprintf(stderr, ", "); } fprintf(stderr, fmt, (x)[_]); } fprintf(stderr, "}\n"); fflush(stderr)
#define debugarr2(x, a, b) cerr << __LINE__ << "::" << #x << " = {"; For(_, a, b) { if (_ != (a)) { cerr << ", "; } cerr << (x)[_]; } cerr << "}\n" << flush

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXA 25
#define MAXB 4

#define rank f
#define suit s

int A, B, ans[9], rank[MAXA], suit[MAXB];
pii C[5];
pii D[5];

void cnt() {
    Fill(rank, 0, A);
    Fill(suit, 0, B);
    FOR(i, 5) {
        rank[C[i].rank]++;
        suit[C[i].suit]++;
    }
    sort(rank, rank + A, greater<int>());
    sort(suit, suit + B, greater<int>());
}

bool four() {
    return rank[0] == 4;
}

bool straight() {
    FOR(i, 5) D[i] = C[i];
    sort(D, D + 5);
    FOR(i, 4) if (D[i].rank + 1 != D[i + 1].rank) return false;
    return true;
}

bool fullhouse() {
    return rank[0] == 3 && rank[1] == 2;
}

bool flush() {
    return suit[0] == 5;
}

bool three() {
    return rank[0] == 3;
}

bool twopair() {
    return rank[0] == 2 && rank[1] == 2;
}

bool onepair() {
    return rank[0] == 2;
}

int main() {
    ri(A);
    ri(B);
    ri(C[0].rank);
    ri(C[0].suit);
    ri(C[1].rank);
    ri(C[1].suit);
    Fill(ans, 0, 9);
    FOR(i, A * B) {
        C[2] = {i / B, i % B};
        if (C[2] == C[0] || C[2] == C[1]) continue;
        For(j, i + 1, A * B) {
            C[3] = {j / B, j % B};
            if (C[3] == C[0] || C[3] == C[1]) continue;
            For(k, j + 1, A * B) {
                C[4] = {k / B, k % B};
                if (C[4] == C[0] || C[4] == C[1]) continue;
                cnt();
                if (straight() && flush()) ans[0]++;
                else if (four()) ans[1]++;
                else if (fullhouse()) ans[2]++;
                else if (flush()) ans[3]++;
                else if (straight()) ans[4]++;
                else if (three()) ans[5]++;
                else if (twopair()) ans[6]++;
                else if (onepair()) ans[7]++;
                else ans[8]++;
            }
        }
    }
    FOR(i, 9) {
        if (i > 0) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");
    return 0;
}
