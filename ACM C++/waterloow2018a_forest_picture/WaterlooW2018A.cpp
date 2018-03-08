#include <bits/stdc++.h>
using namespace std;

#define MAXN 110

int N, M, S, X, Y;
char P[MAXN][MAXN];

inline void print(int X, int Y, char c) {
    if (X >= 0 && X < M && Y >= 0 && Y < M) P[Y][X] = c;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    while (cin >> M >> N) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                P[i][j] = '.';
            }
        }
        for (int i = 0; i < N; i++) {
            cin >> S >> X >> Y;
            if (S == 0) {
                print(X - 1, Y, '_');
                print(X, Y, 'o');
                print(X + 1, Y, '_');
            } else if (S > 0) {
                print(X - 1, Y, '_');
                print(X, Y, '|');
                print(X + 1, Y, '_');
                for (int j = 1; j <= S; j++) {
                    print(X - 1, Y + j, '/');
                    print(X, Y + j, '|');
                    print(X + 1, Y + j, '\\');
                }
                print(X, Y + S + 1, '^');
            }
        }
        for (int i = 0; i < M + 2; i++) {
            cout << '*';
        }
        cout << "\n";
        for (int i = 0; i < M; i++) {
            cout << '*';
            for (int j = 0; j < M; j++) {
                cout << P[M - i - 1][j];
            }
            cout << "*\n";
        }
        for (int i = 0; i < M + 2; i++) {
            cout << '*';
        }
        cout << "\n";
        cout << "\n";
    }
    return 0;
}
