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

#define MAXN 128

int N, W, R, *ans;
string str;

// HELPER FUNCTIONS
int wCnt = 0, rCnt = 0, csCalled = false, p[MAXN];
unordered_set<string> oriSet, newSet;

void init_perm(int n) {
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    shuffle(p, p + n, default_random_engine((unsigned) time(0)));
}

void add_element(string x) {
    if (++wCnt > W) throw runtime_error("Exceeded calls to add_element");
    if (csCalled) throw runtime_error("Cannot call add_element after call to compile_set");
    oriSet.insert(x);
}

void compile_set() {
    if (csCalled) throw runtime_error("Cannot call compile_set more than once");
    csCalled = true;
    for (string oriStr : oriSet) {
        string newStr;
        for (int i = 0; i < N; i++) {
            newStr.pb(oriStr[p[i]]);
        }
        newSet.insert(newStr);
    }
}

bool check_element(string x) {
    if (++rCnt > R) throw runtime_error("Exceeded calls to check_element");
    if (!csCalled) throw runtime_error("Cannot call check_element before call to compile_set");
    return !(newSet.find(x) == newSet.end());
}

void add(int lo, int hi) {
    if (lo == hi) return;
    int m = mid(lo, hi);
    for (int i = 0; i < N; i++) {
        str[i] = '0';
    }
    for (int i = lo; i <= hi; i++) {
        str[i] = '1';
    }
    for (int i = m + 1; i <= hi; i++) {
        str[i] = '0';
        add_element(str);
        str[i] = '1';
    }
    add(lo, m);
    add(m + 1, hi);
}

void check(int lo, int hi, vector<int> &ind) {
    if (lo == hi) {
        ans[ind[0]] = lo;
        return;
    }
    int m = mid(lo, hi);
    for (int i = 0; i < N; i++) {
        str[i] = '0';
    }
    for (int ii : ind) {
        str[ii] = '1';
    }
    vector<int> left, right;
    for (int ii : ind) {
        str[ii] = '0';
        if (check_element(str)) right.pb(ii);
        else left.pb(ii);
        str[ii] = '1';
    }
    check(lo, m, left);
    check(m + 1, hi, right);
}

int* restore_permutation(int n, int w, int r) {
    N = n;
    W = w;
    R = r;
    for (int i = 0; i < N; i++) {
        str.pb('0');
    }
    add(0, N - 1);
    compile_set();
    vector<int> ind;
    for (int i = 0; i < N; i++) {
        ind.pb(i);
    }
    ans = new int[N];
    check(0, N - 1, ind);
    return ans;
}

void grader(int n, int *ans) {
    bool AC = true;
    for (int i = 0; i < n; i++) {
        if (ans[i] != p[i]) AC = false;
    }
    if (AC) printf("AC\n");
    else {
        printf("WA, expected:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", p[i]);
        }
    }
}

int main() {
    int n, w, r;
    ri(n);
    ri(w);
    ri(r);
    init_perm(n);
    int* ans = restore_permutation(n, w, r);
    for (int i = 0; i < n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    grader(n, ans);
    return 0;
}
