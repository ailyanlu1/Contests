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

template<typename T1, typename T2, typename H1 = hash<T1>, typename H2 = hash<T2>>
struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * H1 {}(p.first) + H2 {}(p.second);}};

template <const int ALPHABET_SIZE, const int OFFSET> class SuffixAutomata {
public: // these should really be private
    vector<array<int, ALPHABET_SIZE>> to;
    vector<int> len, link;

private:
    int last;

public:
    void reset() {
        to.clear();
        len.clear();
        link.clear();
        last = 0;
        to.emplace_back();
        to.back().fill(-1);
        len.push_back(0);
        link.push_back(0);
    }

    void addLetter(char c) {
        c -= OFFSET;
        int p = last, q;
        if (to[p][c] != -1) {
            q = to[p][c];
            if (len[q] == len[p] + 1) {
                last = q;
                return;
            }
            to.push_back(to[q]);
            len.push_back(len[p] + 1);
            link.push_back(link[q]);
            link[q] = ((int) link.size()) - 1;
            while (to[p][c] == q) {
                to[p][c] = ((int) to.size()) - 1;
                p = link[p];
            }
        } else {
            last = (int) to.size();
            to.emplace_back();
            to.back().fill(-1);
            len.push_back(len[p] + 1);
            link.push_back(0);
            while (to[p][c] == -1) {
                to[p][c] = last;
                p = link[p];
            }
            if (to[p][c] == last) {
                link[last] = p;
                return;
            }
            q = to[p][c];
            if (len[q] == len[p] + 1) {
                link[last] = q;
                return;
            }
            to.push_back(to[q]);
            len.push_back(len[p] + 1);
            link.push_back(link[q]);
            link[q] = ((int) link.size()) - 1;
            link[last] = ((int) link.size()) - 1;
            while (to[p][c] == q) {
                to[p][c] = ((int) to.size()) - 1;
                p = link[p];
            }
        }
    }

    SuffixAutomata() {
        reset();
    }

    void add(string &s) {
        last = 0;
        for (char c : s) addLetter(c);
    }
};

#define MAXN 20005

int N, SZ[MAXN], ans = -1;
bool isHeavy[MAXN];
vector<int> adj[MAXN];
string S[MAXN];
SuffixAutomata<4, 'A'> SA;

void LCS(string &s) {
    int p = 0, len = 0;
    for (char c : s) {
        c -= 'A';
        while (p != 0 && SA.to[p][c] == -1) {
            p = SA.link[p];
            len = SA.len[p];
        }
        if (SA.to[p][c] != -1) {
            p = SA.to[p][c];
            len++;
        }
        MAX(ans, len);
    }
}

void getSize(int v) {
    SZ[v] = sz(S[v]);
    for (int w : adj[v]) {
        getSize(w);
        SZ[v] += SZ[w];
    }
}

void add(int v) {
    SA.add(S[v]);
    for (int w : adj[v]) if (!isHeavy[w]) add(w);
}

void query(int v) {
    LCS(S[v]);
    for (int w : adj[v]) if (!isHeavy[w]) query(w);
}

void dfs(int v, bool keep = 0) {
    int maxSize = -1, heavyInd = -1;
    for (int w : adj[v]) {
        if (SZ[w] > maxSize) {
            maxSize = SZ[w];
            heavyInd = w;
        }
    }
    for (int w : adj[v]) if (w != heavyInd) dfs(w, 0);
    if (heavyInd != -1) {
        dfs(heavyInd, 1);
        isHeavy[heavyInd] = 1;
    }
    for (int w : adj[v]) {
        if (w != heavyInd) {
            query(w);
            add(w);
        }
    }
    SA.add(S[v]);
    if (heavyInd != -1) isHeavy[heavyInd] = 0;
    if (!keep) SA.reset();
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    FOR(i, N) isHeavy[i] = false;
    int p;
    For(i, 1, N) {
        cin >> p;
        adj[p - 1].pb(i);
    }
    FOR(i, N) {
        cin >> S[i];
        FOR(j, sz(S[i])) {
            if (S[i][j] == 'G') S[i][j] = 'B';
            else if (S[i][j] == 'T') S[i][j] = 'D';
        }
    }
    getSize(0);
    dfs(0, 0);
    cout << ans << nl;
    return 0;
}
