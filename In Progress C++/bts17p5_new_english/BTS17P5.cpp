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

typedef pair<int, pair<int, char>> triple;
#define F f
#define S s.f
#define T s.s
#define mt(a, b, c) mp(a, mp(b, c))

#define MAXNM 100010

int N, M, lastInd[26];
char *word, freeChar = 0;
priority_queue<triple, vector<triple>, greater<triple>> pq;
priority_queue<pair<int, triple>, vector<pair<int, triple>>, greater<pair<int, triple>>> hold;
priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> badChar;
unordered_map<char, int> freq, last;

int main() {
    ri(N);
    ri(M);
    word = new char[N];
    FOR(i, M) {
        triple sug;
        rc(sug.T);
        ri(sug.S);
        ri(sug.F);
        freq[sug.T] = 0;
        last[sug.T] = -1;
        pq.push(sug);
        MAX(lastInd[sug.T - 'a'], sug.F);
    }
    FOR(i, 26) {
        badChar.push(mp(lastInd[i], 'a' + i));
    }
    int ind = 0;
    while (ind < N) {
        while (true) {
            triple cur;
            if (!hold.empty() && hold.top().f <= ind) {
                cur = hold.top().s;
                hold.pop();
            } else if (!pq.empty()) {
                cur = pq.top();
                pq.pop();
            } else {
                break;
            }
            if (ind + cur.S - freq[cur.T] > cur.F || cur.S < freq[cur.T]) {
                printf("-1\n");
                return 0;
            }
            if (ind < last[cur.T]) {
                hold.push(mp(last[cur.T], cur));
                continue;
            }
            int cnt = cur.S - freq[cur.T];
            if (!hold.empty() && (ind + cur.S + (hold.top().s.S - freq[hold.top().s.T]) - hold.top().s.F) > 0) MIN(cnt, ind + cur.S + (hold.top().s.S - freq[hold.top().s.T]) - hold.top().s.F);
            FOR(i, cnt) {
                word[ind++] = cur.T;
            }
            if (cnt < cur.S - freq[cur.T]) pq.push(cur);
            else last[cur.T] = cur.F;
            freq[cur.T] += cnt;
        }
        if (!badChar.empty() && ind >= badChar.top().f) {
            freeChar = badChar.top().s;
            badChar.pop();
        }
        word[ind] = freeChar;
        if (word[ind] == 0) {
            printf("-1\n");
            return 0;
        }
        ind++;
    }
    if (!hold.empty()) {
        printf("-1\n");
        return 0;
    }
    for (int i = 0; i < N; i++) {
        printf("%c", word[i]);
    }
    printf("\n");
    return 0;
}
