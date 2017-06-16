package cco07p3_bowling_for_numbers_plus_plus;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class CCO07P3 {
    private static CCO07P3 o = new CCO07P3();
    public class Reader {
        private BufferedReader in;
        private StringTokenizer st;
        
        public Reader(InputStream inputStream) {
            in = new BufferedReader(new InputStreamReader(inputStream));
        } // Reader InputStream constructor
        
        public Reader(String fileName) throws FileNotFoundException {
            in = new BufferedReader(new FileReader(fileName));
        } // Reader String constructor

        public String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(in.readLine().trim());
            } // while
            return st.nextToken();
        } // next method
        
        public long nextLong() throws IOException {
            return Long.parseLong(next());
        } // nextLong method
        
        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        } // nextInt method
        
        public double nextDouble() throws IOException {
            return Double.parseDouble(next());
        } // nextDouble method
        
        public String nextLine() throws IOException {
            return in.readLine().trim();
        } // nextLine method
    } // Reader class
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        int T = in.nextInt();
        for (int i = 0; i < T; i++) {
            run();
        }
        out.close();
    }
    
    private static int[][] dp;
    private static int[] pins;
    private static int[] psa;
    private static int N, K, W;
    
    public static void run() throws IOException {
        N = in.nextInt();
        K = in.nextInt();
        W = in.nextInt();
        dp = new int[K + 1][N + W + 1];
        for (int i = 0; i <= K; i++) {
            for (int j = 0; j <= N + W; j++) {
                dp[i][j] = -1;
            }
        }
        pins = new int[N + W + 1];
        psa = new int[N + W + 1];
        for (int i = 1; i <= N; i++) {
            pins[i] = in.nextInt();
        }
        for (int i = 1; i <= N + W; i++) {
            psa[i] = psa[i - 1] + pins[i];
        }
        out.println(solve(K, N + W));
    }
    
    public static int solve(int k, int x) {
        if (k <= 0 || x < 0) return 0;
        if (dp[k][x] != -1) return dp[k][x];
        int pos = Math.max(0, x - W);
        int score = psa[x] - psa[pos];
        dp[k][x] = Math.max(solve(k, x - 1), solve(k - 1, pos) + score);
        if (k >= 2) {
            int sum = 0;
            for (int i = pos; i > pos - W + 1 && i > 0; i--) {
                sum += pins[i];
                dp[k][x] = Math.max(dp[k][x], solve(k - 2, i - 1) + score + sum);
            }
        }
        return dp[k][x];
    }
}
