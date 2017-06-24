/*
 * COCI07C3P6_Sqrt_Decomp.cpp
 *
 *  Created on: Jun 24, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
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
#define rc(x) scanf("%c", &x)
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

#define MAXN 250000
#define SQRTN 500

int N, M, arr[MAXN], freq[SQRTN][10], cnt[SQRTN];
string s;

int main() {
    ri(N);
    ri(M);
    cin >> s;
    for (int i = 0; i < N; i++) {
        arr[i] = s[i] - '0';
        freq[i / SQRTN][arr[i]]++;
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        ri(a);
        ri(b);
        a--;
        b--;
        int ans = 0;
        while(a % SQRTN && a <= b) {
            ans += (arr[a] + cnt[a / SQRTN]) % 10;
            freq[a / SQRTN][arr[a]]--;
            arr[a] = (arr[a] + 1) % 10;
            freq[a / SQRTN][arr[a]]++;
            a++;
        }
        while(a + SQRTN <= b) {
            for (int j = 0; j < 10; j++) {
                ans += ((j + cnt[a / SQRTN]) % 10) * freq[a / SQRTN][j];
            }
            cnt[a / SQRTN]++;
            a += SQRTN;
        }
        while (a <= b) {
            ans += (arr[a] + cnt[a / SQRTN]) % 10;
            freq[a / SQRTN][arr[a]]--;
            arr[a] = (arr[a] + 1) % 10;
            freq[a / SQRTN][arr[a]]++;
            a++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
