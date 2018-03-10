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

const int MIN_GALLOP = 7;
const int MIN_MERGE = 32;
const int AUX_SIZE = 256;
const int SMALL_STACK_SIZE = 10;
const int MEDIUM_STACK_SIZE = 20;
const int LARGE_STACK_SIZE = 40;

template <typename T> inline void exch(T *a, T *b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T> void expand(T *&arr, int &curSize, int minSize, int maxSize) {
    if (curSize < minSize) {
        int newSize = minSize;
        newSize |= newSize >> 1;
        newSize |= newSize >> 2;
        newSize |= newSize >> 4;
        newSize |= newSize >> 8;
        newSize |= newSize >> 16;
        newSize++;
        if (newSize < 0) newSize = minSize;
        else newSize = min(newSize, maxSize);
        T *newArr = new T[newSize];
        T *temp = arr;
        arr = newArr;
        delete[] (temp);
        curSize = newSize;
    }
}

////////////////////////// < OPERATOR TIM SORT //////////////////////////

template <typename It> int count_run_and_make_ascending(It st, It en) {
    int n = en - st;
    int i = 1;
    if (i == n) return 1;
    if (st[i++] < st[0]) {
        while (i < n && st[i] < st[i - 1]) i++;
        for (int lo = 0, hi = i - 1; lo < hi; lo++, hi--) exch(st + lo, st + hi);
    } else {
        while (i < n && st[i] >= st[i - 1]) i++;
    }
    return i;
}

template <typename It> void binary_insertion_sort(It st, It en, It ind) {
    typedef typename std::iterator_traits<It>::value_type T;
    if (ind - st == 0) ind++;
    for ( ; ind < en; ind++) {
        T pivot = *ind;
        It left = st, right = ind, mid;
        while (left < right) {
            mid = left + (right - left) / 2;
            if (pivot < *mid) right = mid;
            else left = mid + 1;
        }
        memmove(left + 1, left, (ind - left) * sizeof(T));
        *left = pivot;
    }
}

template <typename T, typename It> int gallop_left(T key, It st, It en, It hint) {
    int ofs = 1, lastOfs = 0;
    if (*hint < key) {
        int maxOfs = en - hint;
        while (ofs < maxOfs && *(hint + ofs) < key) {
            lastOfs=  ofs;
            ofs = ofs * 2 + 1;
            if (ofs <= 0) ofs = maxOfs;
        }
        ofs = min(ofs, maxOfs);
        lastOfs += hint - st;
        ofs += hint - st;
    } else {
        int maxOfs = hint - st + 1;
        while (ofs < maxOfs && *(hint - ofs) >= key) {
            lastOfs = ofs;
            ofs = ofs * 2 + 1;
            if (ofs <= 0) ofs = maxOfs;
        }
        ofs = min(ofs, maxOfs);
        int temp = lastOfs;
        lastOfs = hint - st - ofs;
        ofs = hint - st - temp;
    }
    lastOfs++;
    while (lastOfs < ofs) {
        int m = lastOfs + (ofs - lastOfs) / 2;
        if (*(st + m) < key) lastOfs = m + 1;
        else ofs = m;
    }
    return ofs;
}

template <typename T, typename It> int gallop_right(T key, It st, It en, It hint) {
    int ofs = 1, lastOfs = 0;
    if (key < *hint) {
        int maxOfs = hint - st + 1;
        while (ofs < maxOfs && key < *(hint - ofs)) {
            lastOfs = ofs;
            ofs = ofs * 2 + 1;
            if (ofs <= 0) ofs = maxOfs;
        }
        ofs = min(ofs, maxOfs);
        int temp = lastOfs;
        lastOfs = hint - st - ofs;
        ofs = hint - st - temp;
    } else {
        int maxOfs = en - hint;
        while (ofs < maxOfs && key >= *(hint + ofs)) {
            lastOfs = ofs;
            ofs = ofs * 2 + 1;
            if (ofs <= 0) ofs = maxOfs;
        }
        ofs = min(ofs, maxOfs);
        lastOfs += hint - st;
        ofs += hint - st;
    }
    lastOfs++;
    while (lastOfs < ofs) {
        int m = lastOfs + (ofs - lastOfs) / 2;
        if (key < *(st + m)) ofs = m;
        else lastOfs = m + 1;
    }
    return ofs;
}

template <typename T, typename It> void merge_lo(It st1, It en1, It st2, It en2, T *&aux, int &auxSize, int maxSize) {
    int len1 = en1 - st1, len2 = en2 - st2;
    expand(aux, auxSize, len1, maxSize);
    memmove(aux, st1, len1 * sizeof(T));
    T *cur1 = aux, *cur2 = st2, *dest = st1;
    *(dest++) = *(cur2++);
    if (--len2 == 0) {
        memmove(dest, cur1, len1 * sizeof(T));
        return;
    }
    if (len1 == 1) {
        memmove(dest, cur2, len2 * sizeof(T));
        *(dest + len2) = *(cur1);
        return;
    }
    int minGallop = MIN_GALLOP;
    while (true) {
        bool flag = false;
        int cnt1 = 0, cnt2 = 0;
        do {
            if (*cur2 < *cur1) {
                *(dest++) = *(cur2++);
                cnt2++;
                cnt1 = 0;
                if (--len2 == 0) {
                    flag = true;
                    break;
                }
            } else {
                *(dest++) = *(cur1++);
                cnt1++;
                cnt2 = 0;
                if (--len1 == 1) {
                    flag = true;
                    break;
                }
            }
        } while ((cnt1 | cnt2) < minGallop);
        if (flag) break;
        do {
            cnt1 = gallop_right(*cur2, cur1, cur1 + len1, cur1);
            if (cnt1 != 0) {
                memmove(dest, cur1, cnt1 * sizeof(T));
                dest += cnt1;
                cur1 += cnt1;
                len1 -= cnt1;
                if (len1 <= 1) {
                    flag = true;
                    break;
                }
            }
            *(dest++) = *(cur2++);
            if (--len2 == 0) {
                flag = true;
                break;
            }
            cnt2 = gallop_left(*cur1, cur2, cur2 + len2, cur2);
            if (cnt2 != 0) {
                memmove(dest, cur2, cnt2 * sizeof(T));
                dest += cnt2;
                cur2 += cnt2;
                len2 -= cnt2;
                if (len2 == 0) {
                    flag = true;
                    break;
                }
            }
            *(dest++) = *(cur1++);
            if (--len1 == 1) {
                flag = true;
                break;
            }
            minGallop--;
        } while (cnt1 >= minGallop || cnt2 >= minGallop);
        if (flag) break;
        minGallop = max(minGallop, 0);
        minGallop += 2;
    }
    minGallop = minGallop < 1 ? 1 : minGallop;
    if (len1 == 1) {
        memmove(dest, cur2, len2 * sizeof(T));
        *(dest + len2) = *(cur1);
    } else if (len1 == 0) {
        throw runtime_error("Something wrong with the comparison function.");
    } else if (len2 == 0) {
        memmove(dest, cur1, len1 * sizeof(T));
    } else {
        throw runtime_error("Something wrong with the comparison function.");
    }
}

template <typename T, typename It> void merge_hi(It st1, It en1, It st2, It en2, T *&aux, int &auxSize, int maxSize) {
    int len1 = en1 - st1, len2 = en2 - st2;
    expand(aux, auxSize, len2, maxSize);
    memmove(aux, st2, len2 * sizeof(T));
    T *cur1 = st1 + len1 - 1, *cur2 = aux + len2 - 1, *dest = st2 + len2 - 1;
    *(dest--) = *(cur1--);
    if (--len1 == 0) {
        memmove(dest - len2 + 1, aux, len2 * sizeof(T));
        return;
    }
    if (len2 == 1) {
        dest -= len1;
        cur1 -= len1;
        memmove(dest + 1, cur1 + 1, len1 * sizeof(T));
        *dest = *cur2;
        return;
    }
    int minGallop = MIN_GALLOP;
    while (true) {
        bool flag = false;
        int cnt1 = 0, cnt2 = 0;
        do {
            if (*cur2 < *cur1) {
                *(dest--) = *(cur1--);
                cnt1++;
                cnt2 = 0;
                if (--len1 == 0) {
                    flag = true;
                    break;
                }
            } else {
                *(dest--) = *(cur2--);
                cnt2++;
                cnt1 = 0;
                if (--len2 == 1) {
                    flag = true;
                    break;
                }
            }
        } while ((cnt1 | cnt2) < minGallop);
        if (flag) break;
        do {
            cnt1 = len1 - gallop_right(*cur2, st1, st1 + len1, st1 + len1 - 1);
            if (cnt1 != 0) {
                dest -= cnt1;
                cur1 -= cnt1;
                len1 -= cnt1;
                memmove(dest + 1, cur1 + 1, cnt1 * sizeof(T));
                if (len1 == 0) {
                    flag = true;
                    break;
                }
            }
            *(dest--) = *(cur2--);
            if (--len2 == 1) {
                flag = true;
                break;
            }
            cnt2 = len2 - gallop_left(*cur1, aux, aux + len2, aux + len2 - 1);
            if (cnt2 != 0) {
                dest -= cnt2;
                cur2 -= cnt2;
                len2 -= cnt2;
                memmove(dest + 1, cur2 + 1, cnt2 * sizeof(T));
                if (len2 <= 1) {
                    flag = true;
                    break;
                }
            }
            *(dest--) = *(cur1--);
            if (--len1 == 0) {
                flag = true;
                break;
            }
            minGallop--;
        } while (cnt1 >= minGallop || cnt2 >= minGallop);
        if (flag) break;
        minGallop = max(minGallop, 0);
        minGallop += 2;
    }
    minGallop = minGallop < 1 ? 1 : minGallop;
    if (len2 == 1) {
        dest -= len1;
        cur1 -= len1;
        memmove(dest + 1, cur1 + 1, len1 * sizeof(T));
        *dest = *cur2;
    } else if (len2 == 0) {
        throw runtime_error("Something wrong with the comparison function.");
    } else if (len1 == 0) {
        memmove(dest - len2 + 1, aux, len2 * sizeof(T));
    } else {
        throw runtime_error("Something wrong with the comparison function.");
    }
}

template <typename T, typename It> void merge_runs(It st, It en, int *runBase, int *runLen, int &stackSize, int i, T *&aux, int &auxSize, int maxSize) {
    int base1 = runBase[i];
    int len1 = runLen[i];
    int base2 = runBase[i + 1];
    int len2 = runLen[i + 1];
    runLen[i] = len1 + len2;
    if (i == stackSize - 3) {
        runBase[i + 1] = runBase[i + 2];
        runLen[i + 1] = runLen[i + 2];
    }
    stackSize--;
    int k = gallop_right(st[base2], st + base1, st + base1 + len1, st + base1);
    base1 += k;
    len1 -= k;
    if (len1 == 0) return;
    len2 = gallop_left(st[base1 + len1 - 1], st + base2, st + base2 + len2, st + base2 + len2 - 1);
    if (len2 == 0) return;
    if (len1 <= len2) merge_lo(st + base1, st + base1 + len1, st + base2, st + base2 + len2, aux, auxSize, maxSize);
    else merge_hi(st + base1, st + base1 + len1, st + base2, st + base2 + len2, aux, auxSize, maxSize);
}

template <typename It> void tim_sort(It st, It en) {
    typedef typename std::iterator_traits<It>::value_type T;
    int n = en - st;
    int maxSize = n / 2;
    if (n <= 1) return;
    if (n < MIN_MERGE) {
        int initRunLen = count_run_and_make_ascending(st, en);
        binary_insertion_sort(st, en, st + initRunLen);
        return;
    }
    int auxSize = n < 2 * AUX_SIZE ? n / 2 : AUX_SIZE;
    T *aux = new T[auxSize];
    int maxStackSize = (n < 1000 ? SMALL_STACK_SIZE : (n < 100000 ? MEDIUM_STACK_SIZE : LARGE_STACK_SIZE));
    int *runBase = new int[maxStackSize];
    int *runLen = new int[maxStackSize];
    int stackSize = 0;
    int nn = n, r = 0;
    while (nn >= MIN_MERGE) {
        r |= (nn & 1);
        nn >>= 1;
    }
    int minRun = nn + r;
    int i = 0;
    do {
        int curRunLen = count_run_and_make_ascending(st + i, en);
        if (curRunLen < minRun) {
            int force = min(n, minRun);
            binary_insertion_sort(st + i, st + i + force, st + i + curRunLen);
            curRunLen = force;
        }
        runBase[stackSize] = i;
        runLen[stackSize] = curRunLen;
        stackSize++;
        while (stackSize > 1) {
            int k = stackSize - 2;
            if (k > 0 && runLen[k - 1] <= runLen[k] + runLen[k + 1]) {
                if (runLen[k - 1] < runLen[k + 1]) k--;
                merge_runs(st, en, runBase, runLen, stackSize, k, aux, auxSize, maxSize);
            } else if (runLen[k] <= runLen[k + 1]) {
                merge_runs(st, en, runBase, runLen, stackSize, k, aux, auxSize, maxSize);
            } else {
                break;
            }
        }
        i += curRunLen;
        n -= curRunLen;
    } while (n > 0);
    while (stackSize > 1) {
        int k = stackSize - 2;
        if (k > 0 && runLen[k - 1] < runLen[k + 1]) k--;
        merge_runs(st, en, runBase, runLen, stackSize, k, aux, auxSize, maxSize);
    }
    delete[] (aux);
    delete[] (runBase);
    delete[] (runLen);
}

#define MAXN 100005
#define SQRTN 320

int N, small[SQRTN], large[MAXN], smallSZ = 0, largeSZ = 0;
ll sum = 0;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    int r;
    FOR(i, N) {
        cin >> r;
        small[smallSZ++] = r;
        sum += largeSZ - (upper_bound(large, large + largeSZ, r) - large) + 1;
        for (int j = 0; j < smallSZ; j++) sum += small[j] > r;
        if (smallSZ >= SQRTN) {
            for (int j = 0; j < smallSZ; j++) large[largeSZ++] = small[j];
            smallSZ = 0;
            tim_sort(large, large + largeSZ);
        }
    }
    cout << fixed << setprecision(2) << ((double) sum) / ((double) N) << nl;
    return 0;
}
