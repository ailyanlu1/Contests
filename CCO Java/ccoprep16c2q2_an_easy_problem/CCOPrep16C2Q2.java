package ccoprep16c2q2_an_easy_problem;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class CCOPrep16C2Q2 {
    private static CCOPrep16C2Q2 o = new CCOPrep16C2Q2();
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
        int N = in.nextInt();
        int[] dp = new int[N], last = new int[30];
        for (int i = 0; i < last.length; i++) {
            last[i] = -1;
        }
        int len = 0;
        for (int i = 0; i < N; i++) {
            int a = in.nextInt();
            dp[i] = 1;
            for (int j = 0; a != 0; a >>= 1, j++) {
                if ((a & 1) != 0) {
                    if (last[j] != -1) {
                        dp[i] = Math.max(dp[i], dp[last[j]] + 1);
                    }
                    last[j] = i;
                }
            }
            len = Math.max(len, dp[i]);
        }
        out.println(len);
        out.close();
    }
}
