package dmopc14c3p5_not_enough_servers;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.BitSet;
import java.util.StringTokenizer;

public class DMOPC14C3P5 {
    private static DMOPC14C3P5 o = new DMOPC14C3P5();
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
        int N = in.nextInt();
        int M = in.nextInt();
        int[] s = new int[M];
        BitSet[] dp = new BitSet[1 << N];
        for (int i = 0; i < (1 << N); i++) {
            dp[i] = new BitSet(M);
        }
        for (int i = 0; i < N; i++) {
            int AC = M;
            String S = in.nextLine();
            for (int j = 0; j < M; j++) {
                if (S.charAt(j) == 'X') {
                    s[j] |= 1 << i;
                    AC--;
                }
            }
            if (AC == M) {
                for (int j = 0; j < M; j++) {
                    s[j] |= 1 << i;
                }
            }
        }
        for (int i = 0; i < (1 << N); i++) {
            for (int j = 0; j < M; j++) {
                if (s[j] != 0 && (dp[i].cardinality() > 0 || i == 0)
                        && (dp[i | s[j]].cardinality() > dp[i].cardinality() + 1
                        || dp[i | s[j]].cardinality() == 0)) {
                    dp[i | s[j]] = (BitSet) dp[i].clone();
                    dp[i | s[j]].set(j);
                }
            }
        }
        out.println(dp[(1 << N) - 1].cardinality());
        for (int i = 0; i < M; i++) {
            if (dp[(1 << N) - 1].get(i)) out.print(i + 1 + " ");
        }
        out.println();
        out.close();
    }
}
