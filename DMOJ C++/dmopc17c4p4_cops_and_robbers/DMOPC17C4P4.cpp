#include <bits/stdc++.h>
using namespace std;

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define MIN(a, b) ((a) = min((a), (b)))
#define MAX(a, b) ((a) = max((a), (b)))
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define sz(a) ((int) (a).size())
#define nl "\n"

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

int N, A[MAXN], B[MAXN], cnt[MAXN];
bool done[MAXN];
vector<int> *ind[MAXN], *temp[MAXN];

/**
 * SOLUTION 1: GREEDY APPROACH
 * TIME COMPLEXITY: O(N log N)
 * Sort by frequency, the going from highest to lowest frequency,
 * find first available day to visit bank.
 */

//bool cmpBySz(vector<int> *&a, vector<int> *&b) {
//    return sz(*a) < sz(*b);
//}
//
//bool solve() {
//    FOR(i, N) ind[i] = new vector<int>();
//    FOR(i, N) ind[A[i]]->pb(i);
//    FOR(i, N) done[i] = false;
//    FOR(i, N) B[i] = -1;
//    sort(ind, ind + N, cmpBySz);
//    reverse(ind, ind + N);
//    if (N == 1) return false;
//    FOR(i, N) {
//        if (sz(*ind[i]) != 1) break;
//        if (i == N - 1) {
//            FOR(j, N) B[j] = A[(j + 1) % N];
//            return true;
//        }
//    }
//    int nxt = 0;
//    FOR(i, N) {
//        if (sz(*ind[i]) == 0) break;
//        while (nxt < N && B[nxt] != -1) nxt++;
//        if (nxt == N) return false;
//        int curVal = A[(*ind[i])[0]];
//        int curInd = nxt;
//        while (curInd < N && (B[curInd] != -1 || A[curInd] == curVal)) curInd++;
//        if (curInd == N) return false;
//        B[curInd] = curVal;
//        done[curVal] = true;
//    }
//    FOR(i, N) {
//        if (done[i]) continue;
//        while (nxt < N && B[nxt] != -1) nxt++;
//        if (nxt == N) return false;
//        B[nxt] = i;
//        done[i] = true;
//    }
//    return true;
//}

/**
 * SOLUTION 2: GREEDY APPROACH
 * TIME COMPLEXITY: O(N)
 * Sort by frequency (using counting sort), the going from highest
 * to lowest frequency, find first available day to visit bank.
 */

//void sortBySz() {
//    int maxSZ = 0;
//    FOR(i, N) MAX(maxSZ, sz(*ind[i]));
//    FOR(i, maxSZ + 1) cnt[i] = 0;
//    FOR(i, N) cnt[sz(*ind[i])]++;
//    For(i, 1, maxSZ + 1) cnt[i] += cnt[i - 1];
//    FOR(i, N) temp[--cnt[sz(*ind[i])]] = ind[i];
//    FOR(i, N) ind[i] = temp[i];
//}
//
//bool solve() {
//    FOR(i, N) ind[i] = new vector<int>();
//    FOR(i, N) ind[A[i]]->pb(i);
//    FOR(i, N) done[i] = false;
//    FOR(i, N) B[i] = -1;
//    sortBySz();
//    reverse(ind, ind + N);
//    if (N == 1) return false;
//    FOR(i, N) {
//        if (sz(*ind[i]) != 1) break;
//        if (i == N - 1) {
//            FOR(j, N) B[j] = A[(j + 1) % N];
//            return true;
//        }
//    }
//    int nxt = 0;
//    FOR(i, N) {
//        if (sz(*ind[i]) == 0) break;
//        while (nxt < N && B[nxt] != -1) nxt++;
//        if (nxt == N) return false;
//        int curVal = A[(*ind[i])[0]];
//        int curInd = nxt;
//        while (curInd < N && (B[curInd] != -1 || A[curInd] == curVal)) curInd++;
//        if (curInd == N) return false;
//        B[curInd] = curVal;
//        done[curVal] = true;
//    }
//    FOR(i, N) {
//        if (done[i]) continue;
//        while (nxt < N && B[nxt] != -1) nxt++;
//        if (nxt == N) return false;
//        B[nxt] = i;
//        done[i] = true;
//    }
//    return true;
//}

/**
 * SOLUTION 3: SINGLE ROTATION
 * TIME COMPLEXITY: O(N)
 * Cycle the first occurrence of every blocked bank by 1.
 * Order remaining elements arbitrarily.
 */

bool solve() {
    FOR(i, N) done[i] = false;
    FOR(i, N) B[i] = -1;
    int firstNum = -1;
    int lastInd = -1;
    FOR(i, N) {
        if (done[A[i]]) continue;
        if (lastInd == -1) firstNum = A[i];
        else B[lastInd] = A[i];
        lastInd = i;
        done[A[i]] = true;
    }
    if (lastInd != -1 && A[lastInd] == firstNum) return false;
    if (lastInd != -1) B[lastInd] = firstNum;
    int cur = 0;
    FOR(i, N) {
        if (done[i]) continue;
        while (B[cur] != -1) cur++;
        B[cur] = i;
        done[i] = true;
    }
    return true;
}

/**
 * SOLUTION 4: RANDOM SHUFFLING
 * TIME COMPLEXITY: could go on forever
 * Repeatedly shuffle the array until a permutation has no
 * matches. When checking, move on to the next permutation
 * as soon as a match is found.
 */

//bool solve() {
//    FOR(i, N) done[i] = false;
//    FOR(i, N) B[i] = N - i - 1;
//    int cnt = 0;
//    FOR(i, N) {
//        if (done[A[i]]) continue;
//        cnt++;
//        done[A[i]] = true;
//    }
//    if (cnt == 1) return false;
//    mt19937 rng(time(0));
//    while (true) {
//        FOR(i, N) {
//            if (A[i] == B[i]) break;
//            if (i == N - 1) return true;
//        }
//        FOR(i, N) {
//            int j = i + rng() % (N - i);
//            swap(B[i], B[j]);
//        }
//    }
//}

/**
 * SOLUTION 4: SYSTEMATIC SHUFFLING
 * TIME COMPLEXITY: somewhere between O(N * N!) and O(N!)
 * Iterate through each permutation of the the array until
 * once is found with no matches. When checking, move on to
 * the next permutation as soon as a match is found.
 */

bool tryAll() {
    FOR(i, N) B[i] = i;
    do {
        FOR(i, N) {
            if (A[i] == B[i]) break;
            if (i == N - 1) return true;
        }
    } while (next_permutation(B, B + N));
    return false;
}

void completeTest(int n) {
    N = n;
    int p = pow(N, N);
    int cntWA = 0;
    FOR(i, p) {
        int cur = i;
        FOR(j, N) {
            A[j] = cur % N;
            cur /= N;
        }
        if (solve()) {
            FOR(j, N) done[j] = false;
            FOR(j, N) {
                if (A[j] == B[j] || done[B[j]] || B[j] < 0 || B[j] >= N) {
                    cntWA++;
                    cout << "WRONG ANSWER" << nl;
                    cout << "INPUT:" << nl;
                    cout << N << nl;
                    FOR(k, N) cout << A[k] + 1 << " \n"[k == N - 1];
                    cout << "OUPUT:" << nl;
                    FOR(k, N) cout << B[k] + 1 << " \n"[k == N - 1];
                    cout << "SOLUTION:" << nl;
                    if (tryAll()) FOR(k, N) cout << B[k] + 1 << " \n"[k == N - 1];
                    else cout << -1 << nl;
                    cout << nl;
                    break;
                }
                done[B[j]] = true;
            }
        } else {
            if (tryAll()) {
                cntWA++;
                cout << "WRONG ANSWER" << nl;
                cout << "INPUT:" << nl;
                cout << N << nl;
                FOR(k, N) cout << A[k] + 1 << " \n"[k == N - 1];
                cout << "OUTPUT:" << nl;
                cout << -1 << nl;
                cout << "SOLUTION:" << nl;
                FOR(k, N) cout << B[k] + 1 << " \n"[k == N - 1];
                cout << nl;
            }
        }
    }
    cout << "N = " << N << " ACCURACY: " << setprecision(2) << fixed << 100.00 * ((1 << (4 * N)) - cntWA) / (1 << (4 * N)) << "%" << nl;
    cout.flush();
}

void randomTest(int n) {
    N = n;
    mt19937 rng(time(0));
    FOR(i, N) {
        A[i] = rng() % N;
        assert(0 <= A[i] && A[i] < N);
    }
    const auto start_time = chrono::system_clock::now();
    bool ans = solve();
    const auto end_time = chrono::system_clock::now();
    if (ans) {
        FOR(j, N) done[j] = false;
        FOR(j, N) {
            if (A[j] == B[j] || done[B[j]] || B[j] < 0 || B[j] >= N) {
                cout << "FALSE POSITIVE" << nl;
                cout << "INPUT:" << nl;
                cout << N << nl;
                FOR(k, N) cout << A[k] + 1 << " \n"[k == N - 1];
                cout << "OUPUT:" << nl;
                FOR(k, N) cout << B[k] + 1 << " \n"[k == N - 1];
                cout << nl;
                return;
            }
            done[B[j]] = true;
        }
    }
    double time_elapsed = ((end_time - start_time).count() / static_cast<double>(chrono::system_clock::period::den));
    if (time_elapsed <= 2.0) cout << "N = " << N << " POSSIBLY ACCEPTED" << nl;
    else {
        cout << "N = " << N << " TIME LIMIT EXCEEDED" << nl;
        cout << "INPUT:" << nl;
        cout << N << nl;
        FOR(k, N) cout << A[k] + 1 << " \n"[k == N - 1];
    }
    cout << "Time Elapsed: " << setprecision(3) << fixed << time_elapsed << " sec" << nl;
    cout.flush();
    FOR(i, N) delete ind[i];
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testNum = 0;
    if (testNum == 0) {
        cin >> N;
        FOR(i, N) {
            cin >> A[i];
            A[i]--;
        }
        if (solve()) FOR(i, N) cout << B[i] + 1 << " \n"[i == N - 1];
        else cout << -1 << nl;
    } else if (testNum == 1) {
        For(n, 1, 8) completeTest(n);
    } else {
        randomTest(1000000);
    }
    return 0;
}
