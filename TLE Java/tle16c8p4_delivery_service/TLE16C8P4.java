package tle16c8p4_delivery_service;

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

public class TLE16C8P4 {
    private static TLE16C8P4 o = new TLE16C8P4();
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
    private static long MOD = (long) (1e9 + 7);
    
    public static void main(String[] args) throws IOException {
        int X = in.nextInt();
        if (X == 1) {
            int D = in.nextInt();
            int N = in.nextInt();
            int P = in.nextInt();
            int[] R = new int[D + 1];
            for (int i = 0; i <= D; i++) {
                R[i] = -1;
            }
            for (int i = 0; i < P; i++) {
                R[in.nextInt()] = in.nextInt();
            }
            R[0] = N;
            long[] dp = new long[D + 1];
            long[] pre = new long[D + 2];
            dp[0] = 1;
            long sum = 0;
            for (int i = 0; i <= D; i++) {
                sum = (sum % MOD - pre[i] % MOD + MOD) % MOD;
                if (i > 0) dp[i] = sum % MOD;
                if (R[i] != -1) {
                    int fuel = R[i];
                    sum = (sum % MOD + dp[i] % MOD + MOD) % MOD;
                    if (i + fuel <= D) {
                        pre[i + fuel + 1] = (pre[i + fuel + 1] % MOD + dp[i] % MOD + MOD) % MOD;
                    }
                }
            }
            out.println(dp[D]);
        } else if (X == 2) {
            int W = in.nextInt();
            if (W == 0) {
                out.println("3 1 1");
                out.println("2 1");
            } else {
                int N = (int) (Math.ceil(Math.log(W) / Math.log(2) + 2));
                long[] pow = new long[N + 1];
                pow[1] = 1;
                long[] fuel = new long[N];
                for (int i = 1; i < N; i++) {
                    fuel[i] = N - i - 1;
                    pow[i + 1] = pow[i] * 2;
                }
                StringBuilder str = new StringBuilder();
                int count = 0;
                for (int i = N - 1; i >= 1; i--) {
                    if (pow[i] <= W) {
                        fuel[i] += 1;
                        W -= pow[i];
                    }
                    if (fuel[i] > 0) {
                        str.append(i + " " + fuel[i] + "\n");
                        count++;
                    }
                }
                out.println(N + " " + (N - 1) + " " + count);
                out.println(str);
            }
        }
        out.close();
    }
}
