import std.stdio;
import std.algorithm;

int N;
int[] A;

void main() {
    scanf("%d", &N);
    foreach(i; 0..N) {
        int ai;
        scanf("%d", &ai);
        A ~= ai;
    }
    A.sort();
    foreach(ai; A) writeln(ai);
}
