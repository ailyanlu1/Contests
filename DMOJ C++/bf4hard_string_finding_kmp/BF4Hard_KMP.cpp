/*
 * BF4Hard_KMP.cpp
 *
 *  Created on: Aug 4, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
#define ri(x) scanf("%d", &x)
#define rll(x) scanf("%lld", &x)
#define rllu(x) scanf("%llu", &x)
#define rf(x) scanf("%f", &x)
#define rd(x) scanf("%lf", &x)
#define rc(x) scanf(" %c", &x)
#define rs(x) scanf("%s", x)
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

class KMPStringSearch {
private:
    int *LCP;
    int m;                      // the pattern length;
    char *pattern = nullptr;    // either the character array for the pattern
    string pat = "";            // or the pattern string

public:
    /**
     * Preprocesses the pattern string.
     *
     * @param pat the pattern string
     */
    KMPStringSearch(string pat) {
        this->pat = pat;
        m = pat.length();
        LCP = new int[m + 1];
        LCP[0] = -1;
        for (int i = 0, j = -1; i < m; i++, j++, LCP[i] = j) {
            while (j >= 0 && pat[i] != pat[j]) {
                j = LCP[j];
            }
        }
    }

    /**
     * Preprocesses the pattern string.
     *
     * @param pattern the pattern string
     * @param m the length of the pattern
     */
    KMPStringSearch(char *pattern, int m) {
        this->pattern = pattern;
        this->m = m;
        LCP = new int[m + 1];
        LCP[0] = -1;
        for (int i = 0, j = -1; i < m; i++, j++, LCP[i] = j) {
            while (j >= 0 && pattern[i] != pattern[j]) {
                j = LCP[j];
            }
        }
    }

    /**
     * Returns the index of the first occurrrence of the pattern string
     * in the text string.
     *
     * @param  txt the text string
     * @return the index of the first occurrence of the pattern string
     *         in the text string; -1 if no such match
     */
    int search(string txt) {
        int n = txt.length();
        for (int i = 0, j = 0; i < n; i++, j++) {
            while (j >= 0 && txt[i] != pat[j]) {
                j = LCP[j];
            }
            if (j == m - 1) {
                return i - j;
            }
        }
        return -1;
    }

    /**
     * Returns the index of the first occurrence of the pattern string
     * in the text string.
     *
     * @param  text the text string
     * @param  n the length of the text
     * @return the index of the first occurrence of the pattern string
     *         in the text string; -1 if no such match
     */
    int search(char *text, int n) {
        for (int i = 0, j = 0; i < n; i++, j++) {
            while (j >= 0 && text[i] != pattern[j]) {
                j = LCP[j];
            }
            if (j == m - 1) {
                return i - j;
            }
        }
        return -1;
    }
};

string S, T;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> S >> T;
    KMPStringSearch kmp(T);
    printf("%d\n", kmp.search(S));
    return 0;
}
