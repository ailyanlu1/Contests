package pick_it;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class PickIt {
    private static PickIt o = new PickIt();
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
    private static int[] a;
    private static int[][] dp;
    
    public static void main(String[] args) throws IOException {
        int n;
        while ((n = in.nextInt()) != 0) {
            a = new int[n];
            dp = new int[n + 1][n + 1];
            for (int i = 0; i < n; i++) {
                a[i] = in.nextInt();
            }
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= n; j++) {
                    dp[i][j] = -1;
                }
            }
            out.println(solve(0, n-1));
        }
        out.close();
    }
    
    private static int solve(int l, int r) {
        if (l == r) return 0;
        if (dp[l][r] != -1) return dp[l][r];
        int ans = 0;
        for (int m = l + 1; m < r; m++) {
            ans = Math.max(ans, solve(l, m) + solve(m, r) + a[l] + a[m] + a[r]);
        }
        return dp[l][r] = ans;
    }
}
