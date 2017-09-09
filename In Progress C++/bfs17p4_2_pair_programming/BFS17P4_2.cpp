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

#define WAWA 0
#define WAAC 1
#define ACWA 2
#define ACAC 3

#define AC 1
#define WA 0
#define UN -1

int N, v[MAXN], net[MAXN][4], minCnt, maxCnt;
short cur[MAXN], want[MAXN], temp[MAXN];
char ch;
bool marked[MAXN];
vector<int> u;
string s;

inline pii getMax(int i) {
    int maxVal = 0;
    int maxInd = 0;
    FOR(j, 4) {
        if ((net[i][j] == maxVal && 1 - ((j / 2) ^ (j % 2)) == WA)) marked[i] = true;
        if (net[i][j] > maxVal || (net[i][j] == maxVal && 1 - ((j / 2) ^ (j % 2)) == WA)) {
            maxVal = net[i][j];
            maxInd = j;
        }
    }
    return mp(maxVal, maxInd);
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    For(i, 1, N + 1) {
        cin >> ch;
        if (ch == 'C') {
            cin >> s;
            v[i] = 0;
            if (s == "AC") cur[i] = AC;
            else if (s == "WA") cur[i] = WA;
            else {
                u.pb(i);
                cur[i] = UN;
            }
        } else if (ch == 'E') {
            cin >> v[i];
            cin >> s;
            if (s == "AC") cur[i] = AC;
            else if (s == "WA") cur[i] = WA;
            else {
                u.pb(i);
                cur[i] = UN;
            }
        } else {
            i--;
        }
    }
    maxCnt = 0;
    Rev(i, N, 0) {
        pii m = getMax(i);
        if (m.f == 0) want[i] = 0;
        else want[i] = 1 - ((m.s / 2) ^ (m.s % 2));
        if (cur[i] == UN) cur[i] = want[i];
        net[v[i]][cur[i] * 2 + want[i]]++;
    }
    For(i, 1, N + 1) {
        temp[i] = cur[i];
    }
    For(i, 1, N + 1) {
        if (v[i] != 0) cur[i] ^= !cur[v[i]];
        if (!cur[i]) maxCnt++;
    }
    For(i, 1, N + 1) {
        cur[i] = temp[i];
    }
    minCnt = 0;
    for (int &i : u) {
        if (!marked[i]) cur[i] = !cur[i];
    }
    For(i, 1, N + 1) {
        if (v[i] != 0) cur[i] ^= !cur[v[i]];
        if (!cur[i]) minCnt++;
    }
    printf("%d %d\n", minCnt, maxCnt);
    return 0;
}
