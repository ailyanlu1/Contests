#include <cstdio>
#include <deque>
using namespace std;

#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    int N, M, C;
    bool ans = false;
    scan(N);
    scan(M);
    scan(C);
    deque<pair<int, int>> mindq, maxdq;
    int a;
    for (int i = 0; i < N; i++) {
        scan(a);
        while (!mindq.empty() && mindq.front().first <= i - M) mindq.pop_front();
        while (!maxdq.empty() && maxdq.front().first <= i - M) maxdq.pop_front();
        while (!mindq.empty() && mindq.back().second >= a) mindq.pop_back();
        while (!maxdq.empty() && maxdq.back().second <= a) maxdq.pop_back();
        mindq.emplace_back(i, a);
        maxdq.emplace_back(i, a);
        if (i >= M - 1 && maxdq.front().second - mindq.front().second <= C) {
            ans = true;
            printf("%d\n", i - M + 2);
        }
    }
    if (!ans) printf("NONE\n");
    return 0;
}
