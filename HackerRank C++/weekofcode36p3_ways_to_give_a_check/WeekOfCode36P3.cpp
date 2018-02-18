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

int t;
pii black_king, white_king;
char board[8][8];
pii dir[8] = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};

bool checkBishop(int r, int c, pii king) {
    for (int i = r - 1, j = c - 1; i >= 0 && j >= 0; i--, j--) {
        if (king == mp(i, j)) return true;
        if (board[i][j] != '#') break;
    }
    for (int i = r - 1, j = c + 1; i >= 0 && j < 8; i--, j++) {
        if (king == mp(i, j)) return true;
        if (board[i][j] != '#') break;
    }
    for (int i = r + 1, j = c - 1; i < 8 && j >= 0; i++, j--) {
        if (king == mp(i, j)) return true;
        if (board[i][j] != '#') break;
    }
    for (int i = r + 1, j = c + 1; i < 8 && j < 8; i++, j++) {
        if (king == mp(i, j)) return true;
        if (board[i][j] != '#') break;
    }
    return false;
}

bool checkRook(int r, int c, pii king) {
    for (int i = r, j = c - 1; j >= 0; j--) {
        if (king == mp(i, j)) return true;
        if (board[i][j] != '#') break;
    }
    for (int i = r, j = c + 1; j < 8; j++) {
        if (king == mp(i, j)) return true;
        if (board[i][j] != '#') break;
    }
    for (int i = r - 1, j = c; i >= 0; i--) {
        if (king == mp(i, j)) return true;
        if (board[i][j] != '#') break;
    }
    for (int i = r + 1, j = c; i < 8; i++) {
        if (king == mp(i, j)) return true;
        if (board[i][j] != '#') break;
    }
    return false;
}

bool checkKnight(int r, int c, pii king) {
    FOR(i, 8) if (mp(r + dir[i].f, c + dir[i].s) == king) return true;
    return false;
}

bool incheck() {
    FOR(i, 8) {
        FOR(j, 8) {
            if (board[i][j] == 'q') {
                if (checkBishop(i, j, white_king) || checkRook(i, j, white_king)) return true;
            } else if (board[i][j] == 'n') {
                if (checkKnight(i, j, white_king)) return true;
            } else if (board[i][j] == 'b') {
                if (checkBishop(i, j, white_king)) return true;
            } else if (board[i][j] == 'r') {
                if (checkRook(i, j, white_king)) return true;
            }
        }
    }
    return false;
}

int main() {
    ri(t);
    char c;
    FOR(tt, t) {
        int cnt = 0;
        FOR(i, 8) {
            FOR(j, 8) {
                sc(c);
                if (c == 'k') black_king = mp(7 - i, j);
                else if (c == 'K') white_king = mp(7 - i, j);
                board[7 - i][j] = c;
            }
        }
        FOR(k, 8) {
            if (board[6][k] == 'P' && board[7][k] == '#') {
                board[6][k] = '#';
                board[7][k] = 'X';
                if (incheck()) {
                    board[6][k] = 'P';
                    board[7][k] = '#';
                    continue;
                }
                cnt += checkBishop(7, k, black_king);
                cnt += checkRook(7, k, black_king);
                if (cnt >= 1) cnt++;
                cnt += checkKnight(7, k, black_king);
                bool done = false;
                FOR(i, 8) {
                    FOR(j, 8) {
                        if (board[i][j] == 'Q') {
                            if (checkBishop(i, j, black_king) || checkRook(i, j, black_king)) cnt = 4;
                            done = true;
                        } else if (board[i][j] == 'N') {
                            if (checkKnight(i, j, black_king)) cnt = 4;
                            done = true;
                        } else if (board[i][j] == 'B') {
                            if (checkBishop(i, j, black_king)) cnt = 4;
                            done = true;
                        } else if (board[i][j] == 'R') {
                            if (checkRook(i, j, black_king)) cnt = 4;
                            done = true;
                        }
                        if (done) break;
                    }
                    if (done) break;
                }
                break;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
