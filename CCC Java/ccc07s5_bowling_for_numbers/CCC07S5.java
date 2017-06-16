package ccc07s5_bowling_for_numbers;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class CCC07S5 {
    private static CCC07S5 o = new CCC07S5();
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
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    public static void main(String[] args) throws IOException {
        int t = in.nextInt();
        for (int i = 0; i < t; i++) {
            run();
        }
        out.close();
    }
    
    public static void run() throws IOException {
        int n = in.nextInt();
        int k = in.nextInt();
        int w = in.nextInt();
        int[] pins = new int[n];
        int[] sum = new int[n];
        int[][] dp = new int[k + 1][n];
        for (int i = 0; i < n; i++) {
            pins[i] = in.nextInt();
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < w && j <= i; j++) {
                sum[i] += pins[i - j];
            }
        }
        for (int i = 1; i <= k; i++) {
            dp[i][0] = pins[0];
        }
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j < n; j++) {
                int temp = sum[j];
                if (j >= w) {
                    temp += dp[i - 1][j - w];
                }
                dp[i][j] = Math.max(temp, dp[i][j - 1]);
            }
        }
        out.println(dp[k][n - 1]);
    }
}
