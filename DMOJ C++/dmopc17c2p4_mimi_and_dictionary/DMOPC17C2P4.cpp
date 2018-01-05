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
#define Fill(a, x, n) FOR(_, n) (a)[_] = (x)
#define randi(a, b) (rand() % ((b) - (a) + 1) + (a))

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
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
typedef map<ll, ll> mll;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;
typedef unordered_map<ll, ll> umll;

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

class ZAlgorithm {
private:
    string text;
    int *z;

    void compute() {
        int l = 0, r = 0;
        for (int i = 1; i < text.length(); i++) {
            if (i > r) {
                l = r = i;
                while (r < text.length() && text[r] == text[r - l]) r++;
                r--;
                z[i] = r - l + 1;
            } else {
                int j = i - l;
                if (z[j] < r - i + 1) z[i] = z[j];
                else {
                    l = i;
                    while (r < text.length() && text[r] == text[r - l]) r++;
                    r--;
                    z[i] = r - l + 1;
                }
            }
        }
    }

public:
    ZAlgorithm(string text) {
        this->text = text;
        z = new int[text.length()];
        compute();
    }

    int getPrefixSubstringLength(int i) {
        return z[i];
    }

    int* getPrefixSubstringLengths() {
        return z;
    }
};

int longestPalindromePrefix(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    string t = s + "#" + rev;
    int LCP[t.length() + 1];
    LCP[0] = -1;
    for (int i = 0, j = -1; i < t.length(); i++, j++, LCP[i] = j) {
        while (j >= 0 && t[i] != t[j]) {
            j = LCP[j];
        }
    }
    return LCP[t.length()];
}

string str;
ZAlgorithm *z;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> str;
    z = new ZAlgorithm(str);
    int len = 0;
    For(i, 1, str.length()) MAX(len, z->getPrefixSubstringLength(i));
    printf("%d\n", longestPalindromePrefix(str.substr(0, len)));
    return 0;
}
