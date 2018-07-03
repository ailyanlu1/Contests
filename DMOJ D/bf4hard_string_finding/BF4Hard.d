import std.stdio;
import std.algorithm;
import std.string;

char[] S, T;
int[] LCP;

void main() {
    readln(S);
    readln(T);
    S = strip(S);
    T = strip(T);
    foreach (i; 0..T.length + 1) LCP ~= 0;
    LCP[0] = -1;
    for (int i = 0, j = -1; i < T.length; i++, j++, LCP[i] = (i != T.length && T[i] == T[j]) ? LCP[j] : j) {
        while (j >= 0 && T[i] != T[j]) j = LCP[j];
    }
    for (int i = 0, j = 0; i < S.length; i++, j++) {
        while (j >= 0 && S[i] != T[j]) j = LCP[j];
        if (j == T.length - 1) {
            writeln(i - j);
            return;
        }
    }
    writeln(-1);
}
