#include <bits/stdc++.h>

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
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define For(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Forit(i, c) for (auto i = (c).begin(); i != (c).end(); i++)
#define Rev(i, a, b) for (int i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define Revit(i, c) for (auto i = (c).rbegin(); i != (c).rend(); i++)
#define FILL(a, x) memset((a), (x), sizeof(a))
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x);
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<int, float> pif;
typedef pair<float, int> pfi;
typedef pair<double, double> pdd;
typedef pair<int, double> pid;
typedef pair<double, int> pdi;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pill;
typedef pair<ll, int> plli;
typedef pair<llu, llu> pllu;
typedef pair<int, llu> pillu;
typedef pair<llu, int> pllui;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXN 100010
int N, v[MAXN];
vector<int> u;
short cur[MAXN], temp[MAXN];
char ch;
string s;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    For(i, 1, N + 1) {
        cin >> ch;
        if (ch == 'C') {
            cin >> s;
            v[i] = 0;
            if (s == "AC") cur[i] = 1;
            else if (s == "WA") cur[i] = 0;
            else {
                cur[i] = -1;
                u.pb(i);
            }
        } else if (ch == 'E') {
            cin >> v[i];
            cin >> s;
            if (s == "AC") cur[i] = 1;
            else if (s == "WA") cur[i] = 0;
            else {
                cur[i] = -1;
                u.pb(i);
            }
        } else {
            i--;
        }
    }
    int minCnt = INT_MAX;
    int maxCnt = INT_MIN;
    int cnt = 0;
    FOR(i, 1 << (int) (u.size())) {
        cnt = 0;
        FOR(j, (int) (u.size())) {
            cur[u[j]] = i & (1 << j) ? 1 : 0;
        }
        For(j, 1, N + 1) {
            temp[j] = cur[j];
        }
        For(j, 1, N + 1) {
            if (v[j] != 0) cur[j] ^= !cur[v[j]];
            if (!cur[j]) cnt++;
        }
        MIN(minCnt, cnt);
        MAX(maxCnt, cnt);
        For(j, 1, N + 1) {
            cur[j] = temp[j];
        }
    }
    printf("%d %d\n", minCnt, maxCnt);
    return 0;
}
