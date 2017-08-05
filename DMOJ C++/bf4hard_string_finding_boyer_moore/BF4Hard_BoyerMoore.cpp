/*
 * BF4Hard_BoyerMoore.cpp
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

class BoyerMooreStringSearch {
private:
    int R;                    // the radix
    int *right;               // the bad-character skip array
    int m;                    // the length of the pattern
    char *pattern = nullptr;  // store the pattern as a character array
    string pat = "";          // or as a string

public:
    /**
     * Preprocesses the pattern string.
     *
     * @param pat the pattern string
     */
    BoyerMooreStringSearch(string pat) {
        this->R = 256;
        this->pat = pat;
        this->m = pat.length();
        // position of rightmost occurrence of c in the pattern
        right = new int[R];
        for (int c = 0; c < R; c++)
            right[c] = -1;
        for (int j = 0; j < m; j++)
            right[pat[j]] = j;
    }

    /**
     * Preprocesses the pattern string.
     *
     * @param pattern the pattern string
     * @param m the length of the pattern
     * @param R the alphabet size
     */
    BoyerMooreStringSearch(char *pattern, int m, int R) {
        this->R = R;
        this->m = m;
        this->pattern = pattern;
        // position of rightmost occurrence of c in the pattern
        right = new int[R];
        for (int c = 0; c < R; c++)
            right[c] = -1;
        for (int j = 0; j < m; j++)
            right[pattern[j]] = j;
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
        int skip;
        for (int i = 0; i <= n - m; i += skip) {
            skip = 0;
            for (int j = m-1; j >= 0; j--) {
                if (pat[j] != txt[i+j]) {
                    skip = max(1, j - right[txt[i+j]]);
                    break;
                }
            }
            if (skip == 0) return i;    // found
        }
        return -1;                      // not found
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
        int skip;
        for (int i = 0; i <= n - m; i += skip) {
            skip = 0;
            for (int j = m-1; j >= 0; j--) {
                if (pattern[j] != text[i+j]) {
                    skip = max(1, j - right[text[i+j]]);
                    break;
                }
            }
            if (skip == 0) return i;    // found
        }
        return -1;                      // not found
    }
};

string S, T;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> S >> T;
    BoyerMooreStringSearch bm(T);
    printf("%d\n", bm.search(S));
    return 0;
}
