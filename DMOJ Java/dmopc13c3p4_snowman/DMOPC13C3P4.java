package dmopc13c3p4_snowman;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Collections;
import java.util.StringTokenizer;

public class DMOPC13C3P4 {
    private static BufferedReader in;
    private static StringTokenizer st;
    private static PrintWriter out;
    
    public static String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(in.readLine().trim());
        } // while
        return st.nextToken();
    } // next method
    
    public static long nextLong() throws IOException {
        return Long.parseLong(next());
    } // nextLong method
    
    public static int nextInt() throws IOException {
        return Integer.parseInt(next());
    } // nextInt method
    
    public static double nextDouble() throws IOException {
        return Double.parseDouble(next());
    } // nextDouble method
    
    public static String nextLine() throws IOException {
        return in.readLine().trim();
    } // nextLine method
    
    private static int M, N, S;
    private static Integer[] B;
    private static char[][] grid;
    
    public static void main(String[] args) throws IOException {
        in = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(new OutputStreamWriter(System.out));
        M = nextInt();
        N = nextInt();
        grid = new char[M][N];
        S = nextInt();
        int sum = 0;
        B = new Integer[S];
        for (int i = 0; i < S; i++) sum += B[i] = nextInt();
        Arrays.sort(B, Collections.reverseOrder());
        int count = 0;
        for (int i = 0; i < M; i++) {
            grid[i] = next().toCharArray();
            for (int j = 0; j < N; j++) count += grid[i][j] == '0' ? 1 : 0;
        }
        if (sum > count) out.println("no");
        else out.println(solve(0) ? "yes" : "no");
        out.close();
    }
    
    private static boolean solve(int b) {
        if (b == S) return true;
        boolean add = false;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (i + B[b] <= M) {
                    add = true;
                    for (int k = 0; k < B[b]; k++) {
                        if (grid[i + k][j] == '1') {
                            add = false;
                            break;
                        }
                    }
                    if (add) {
                        for (int k = 0; k < B[b]; k++) grid[i + k][j] = '1';
                        if (solve(b + 1)) return true;
                        for (int k = 0; k < B[b]; k++) grid[i + k][j] = '0';
                    }
                }
                if (j + B[b] <= N) {
                    add = true;
                    for (int k = 0; k < B[b]; k++) {
                        if (grid[i][j + k] == '1') {
                            add = false;
                            break;
                        }
                    }
                    if (add) {
                        for (int k = 0; k < B[b]; k++) grid[i][j + k] = '1';
                        if (solve(b + 1)) return true;
                        for (int k = 0; k < B[b]; k++) grid[i][j + k] = '0';
                    }
                }
            }
        }
        return false;
    }
}
