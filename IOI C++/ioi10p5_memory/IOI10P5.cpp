#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
#define mid(x, y) (x + (y - x) / 2)
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
#define randi(a, b) (rand() % (b - a + 1) + a)

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

// HELPER FUNCTIONS
const int _numLetters = 25;
int _calls = 0;
char _cards[_numLetters * 2], _first;
unordered_set<char> _candies;
void init_perm() {
    for (int i = 0; i < _numLetters; i++) {
        _cards[i] = _cards[_numLetters + i] = 'A' + i;
    }
    shuffle(_cards, _cards + _numLetters, default_random_engine((unsigned) time(0)));
}

char faceup(int c) {
    _calls++;
    if (_calls % 2 == 1) _first = _cards[c - 1];
    else if (_first == _cards[c - 1]) _candies.insert(_cards[c - 1]);
    return _cards[c - 1];
}

void grader() {
    if (_candies.size() == 25) printf("All candies found.\n");
    else printf("Not all candies found\n");
    if (_calls <= 100) printf("Finished in at most 100 calls to faceup.\n");
    else printf("Exceeded 100 calls to faceup.\n");
}
// END HELPER

#define NUML 25

vector<int> num[NUML];

void play() {
    for (int i = 1; i <= 50; i++) {
        num[faceup(i) - 'A'].pb(i);
    }
    for (int i = 0; i < NUML; i++) {
        for (int j : num[i]) {
            faceup(j);
        }
    }
}

int main() {
    init_perm();
    play();
    grader();
    return 0;
}
