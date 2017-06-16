package dp1p3_longest_increasing_subsequence;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class DP1P3 {
    private static DP1P3 o = new DP1P3();
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
    
    public static class LongestIncreasingSubsequence {
        
        private LongestIncreasingSubsequence() {}
        
        /** 
         * Static method for determining the length of the longest increasing subsequence.
         * 
         * Takes time proportional to <em>N</em> log <em>N</em> where N is the length of the sequence.
         * 
         * Takes space proportional to <em>N</em>.
         * 
         * @param sequence the array of integers to check
         * @return the length of the longest increasing subsequence
         */
        public static int solve(int[] sequence) {
            int[] dp = new int[sequence.length];
            int len = 0;
            for (int x: sequence) {
                int i = Arrays.binarySearch(dp, 0, len, x);
                if (i < 0) i = -(i + 1);
                dp[i] = x;
                if (i == len) len++;
            }
            return len;
        } 
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int[] arr = new int[N];
        for (int i = 0; i < N; i++) {
            arr[i] = in.nextInt();
        }
        out.println(LongestIncreasingSubsequence.solve(arr));
        out.close();
    }
}
