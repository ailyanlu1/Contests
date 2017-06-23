package utso15p3_pogo;

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

public class UTSO15P3 {
    private static UTSO15P3 o = new UTSO15P3();
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
    private static int dp[][];
    private static int MOD = (int) (1e9 + 7);
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int M = in.nextInt();
        dp = new int[N + 1][5];
        if (M == 1) out.println(1);
        else if (M == 2) out.println(solve2(N));
        else out.println(solve3(N, 0));
        out.close();
    }
    
    private static int solve2(int n) {
        if (n <= 0) return 0;
        if (n == 1) return 1;
        if (dp[n][0] != 0) return dp[n][0];
        return dp[n][0] = (solve2(n - 1) + solve2(n - 3)) % MOD;
    }
    
    private static int solve3(int n, int x) {
        if (n <= 0) return 0;
        if (n == 1 && x == 0) return 1;
        if (dp[n][x] != 0) return dp[n][x];
        if (x == 0) return dp[n][x] = ((solve3(n - 1, 0) % MOD + solve3(n - 2, 1)) % MOD + solve3(n - 3, 2)) % MOD;
        else if (x == 1) return dp[n][x] = (((solve3(n - 2, 0) % MOD + solve3(n - 3, 3)) % MOD + solve3(n - 1, 4)) % MOD + solve3(n - 3, 4)) % MOD;
        else if (x == 2) return dp[n][x] = (solve3(n - 2, 0) % MOD + solve3(n, 3)) % MOD;
        else if (x == 3) return dp[n][x] = ((((solve3(n - 1, 0) % MOD + solve3(n - 2, 0)) % MOD + solve3(n - 3, 3)) % MOD + solve3(n - 1, 4)) % MOD + solve3(n - 3, 4)) % MOD;
        else return dp[n][x] = (solve3(n, 0) % MOD + solve3(n - 1, 1)) % MOD;
    }
}
