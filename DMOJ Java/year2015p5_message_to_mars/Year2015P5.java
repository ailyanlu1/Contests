package year2015p5_message_to_mars;

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

public class Year2015P5 {
    private static Year2015P5 o = new Year2015P5();
    public class Reader {
        private BufferedReader in;
        private StringTokenizer st;

        public Reader(InputStream inputStream) {
            in = new BufferedReader(new InputStreamReader(inputStream));
        }

        public Reader(String fileName) throws FileNotFoundException {
            in = new BufferedReader(new FileReader(fileName));
        }

        public String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(in.readLine().trim());
            }
            return st.nextToken();
        }

        public String next(String delim) throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(in.readLine().trim());
            }
            return st.nextToken(delim);
        }

        /*
        public BigInteger nextBigInteger() throws IOException {
            return new BigInteger(next());
        }
        */

        public byte nextByte() throws IOException {
            return Byte.parseByte(next());
        }

        public byte nextByte(String delim) throws IOException {
            return Byte.parseByte(next(delim));
        }

        public char nextChar() throws IOException {
            return next().charAt(0);
        }

        public char nextChar(String delim) throws IOException {
            return next(delim).charAt(0);
        }

        public double nextDouble() throws IOException {
            return Double.parseDouble(next());
        }

        public double nextDouble(String delim) throws IOException {
            return Double.parseDouble(next(delim));
        }

        public float nextFloat() throws IOException {
            return Float.parseFloat(next());
        }

        public float nextFloat(String delim) throws IOException {
            return Float.parseFloat(next(delim));
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        public int nextInt(String delim) throws IOException {
            return Integer.parseInt(next(delim));
        }

        public long nextLong() throws IOException {
            return Long.parseLong(next());
        }

        public long nextLong(String delim) throws IOException {
            return Long.parseLong(next(delim));
        }

        public short nextShort() throws IOException {
            return Short.parseShort(next());
        }

        public short nextShort(String delim) throws IOException {
            return Short.parseShort(next(delim));
        }

        public String nextLine() throws IOException {
            st = null;
            return in.readLine();
        }
    } // Reader class
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    private static String text;
    private static int[] T;
    private static BitSet[] dp;
    private static final int MAXS = 2000;
    
    private static void failure(String pat) {
        T[0] = -1;
        for (int i = 0, j = -1; i < pat.length(); i++, j++, T[i] = j) {
            while (j >= 0 && pat.charAt(i) != pat.charAt(j)) {
                j = T[j];
            }
        }
    }
    
    private static void KMP(String pat) {
        for (int i = 0, j = 0; i < text.length(); i++, j++) {
            while (j >= 0 && text.charAt(i) != pat.charAt(j)) {
                j = T[j];
            }
            if (j == pat.length() - 1) {
                dp[i - j].set(i + 1);
                j = T[j];
            }
        }
    }
    
    public static void main(String[] args) throws IOException {
        text = in.nextLine();
        int N = in.nextInt();
        T = new int[MAXS + 1];
        dp = new BitSet[MAXS + 1];
        for (int i = 0; i <= MAXS; i++) {
            dp[i] = new BitSet(MAXS + 1);
        }
        for (int i = 0; i < N; i++) {
            String pat = in.nextLine();
            failure(pat);
            KMP(pat);
        }
        int ans = 0;
        for (int i = 0; i < text.length(); i++) {
            for (int j = i + 1; j < text.length(); j++) {
                if (dp[i].get(j)) {
                    dp[i].or(dp[j]);
                }
            }
            ans += dp[i].cardinality();
        }
        out.println(ans);
        out.close();
    }
}
