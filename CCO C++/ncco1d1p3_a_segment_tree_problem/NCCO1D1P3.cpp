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

template<typename T1, typename T2> struct pair_hash {size_t operator ()(const pair<T1, T2> &p) const {return 31 * hash<T1> {}(p.first) + hash<T2> {}(p.second);}};

#define MAXN 1000005

int N, M, C, A[MAXN];
bool ans = false;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> C;
    deque<int> mindq, maxdq;
    FOR(i, N) {
        cin >> A[i];
        while (!mindq.empty() && mindq.front() <= i - M) mindq.pop_front();
        while (!maxdq.empty() && maxdq.front() <= i - M) maxdq.pop_front();
        while (!mindq.empty() && A[mindq.back()] >= A[i]) mindq.pop_back();
        while (!maxdq.empty() && A[maxdq.back()] <= A[i]) maxdq.pop_back();
        mindq.push_back(i);
        maxdq.push_back(i);
        if (i >= M - 1 && A[maxdq.front()] - A[mindq.front()] <= C) {
            ans = true;
            cout << i - M + 2 << nl;
        }
    }
    if (!ans) cout << "NONE" << nl;
    return 0;
}
