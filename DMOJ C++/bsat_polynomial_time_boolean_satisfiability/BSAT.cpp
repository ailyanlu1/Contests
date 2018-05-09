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

// solves half of the problem by iterating through each permutation
// each element can either be in the subset, or not in the subset
template <typename T> long long solveHalf(vector<T> &half, vector<T> &sum, T value) {
    long long ret = 0;
    for (int i = 1; i < (1 << (int) half.size()); i++) {
        T curSum = 0;
        for (int j = 0; j < (int) half.size(); j++) if (i & (1 << j)) curSum += half[j];
        sum.push_back(curSum);
        if (curSum <= value) ret++;
    }
    sort(sum.begin(), sum.end());
    return ret;
}

/**
 * Finds the number of subsets that sum less than or equal to a value.
 *
 * Uses a meet in the middle approach to reduce the runtime from O(N * 2 ^ N) to O(N * 2 ^ (N / 2))
 *
 * @param all the set of all elements
 * @return the number of subsets that sum less than or equal to a value
 */
template <typename T> long long solve(vector<T> &all, T value) {
    long long ret = 0;
    vector<T> even, odd;
    even.reserve(all.size() / 2 + all.size() % 2);
    odd.reserve(all.size() / 2);
    vector<T> evenSum, oddSum;
    evenSum.reserve(1 << (all.size() / 2 + all.size() % 2));
    oddSum.reserve(1 << (all.size() / 2));
    for (int i = 0; i < (int) all.size(); i++) {
        if (i % 2 == 0) even.push_back(all[i]);
        else odd.push_back(all[i]);
    }
    ret += solveHalf(even, evenSum, value);
    ret += solveHalf(odd, oddSum, value);
    if (value >= 0) ret++;
    int j = ((int) oddSum.size()) - 1;
    for (int i = 0; i < (int) evenSum.size(); i++) {
        while (j >= 0 && evenSum[i] + oddSum[j] > value) j--;
        ret += j + 1;
    }
    return ret;
}

int N;
ll K;
vector<ll> vals;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    vals.reserve(N);
    ll ni;
    FOR(i, N) {
        cin >> ni;
        vals.pb(ni);
    }
    cout << solve(vals, K) << nl;
    return 0;
}
