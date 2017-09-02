package ecoo17r2p4_zig_zag;

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

public class ECOO17R2P4 {
    private static ECOO17R2P4 o = new ECOO17R2P4();
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

        /*public BigInteger nextBigInteger() throws IOException {
            return new BigInteger(next());
        }*/

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
    
    private static final int NUM_OF_TEST_CASES = 10; // TODO CHANGE NUMBER OF TEST CASES
    private static final int MOD = (int) (1e9 + 7);
    public static void main(String[] args) throws IOException {
        for (int i = 1; i <= NUM_OF_TEST_CASES; i++) {
            run(i);
        }
        out.close();
    }
    
    public static void run(int testCaseNum) throws IOException {
        int N = in.nextInt();
        long [][] dp = new long[2][N + 2];
        dp[1][1] = 1;
        for (int i = 2; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i % 2 == 0) {
                    dp[0][j] = (dp[1][j - 1] + dp[0][j - 1]) % MOD;
                    dp[0][j + 1] = dp[0][j];
                } else {
                    if (i <= j) break;
                    dp[1][j] = (dp[0][i] - dp[0][j - 1] + dp[1][j - 1] + MOD) % MOD;
                    dp[1][j + 1] = dp[1][j];
                }
            }
        }
        out.println(dp[N % 2][N] % MOD);
    }
}
