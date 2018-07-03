#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) ((int) (a).size())
#define nl '\n'
#define sp ' '

int N;
string S;
map<int, int> freq;
int mapping[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> S;
        int val = 0;
        for (int j = 0; j < sz(S); j++) {
            if (S[j] >= '0' && S[j] <= '9') {
                val *= 10;
                val += S[j] - '0';
            } else if (S[j] >= 'A' && S[j] <= 'Z') {
                val *= 10;
                val += mapping[S[j] - 'A'];
            }
        }
        freq[val]++;
    }
    int cnt = 0;
    for (pair<int, int> p : freq) {
        if (p.second >= 2) {
            cout << setw(3) << setfill('0') << p.first / 10000;
            cout << '-';
            cout << setw(4) << setfill('0') << p.first % 10000;
            cout << sp << p.second << nl;
            cnt++;
        }
    }
    if (cnt == 0) cout << "No duplicates." << nl;
    return 0;
}
