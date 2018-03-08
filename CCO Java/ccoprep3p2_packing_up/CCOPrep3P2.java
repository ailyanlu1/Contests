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

public class CCOPrep3P2 {
    private static CCOPrep3P2 o = new CCOPrep3P2();
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
    private static long[] len, dp;
    private static int[] ind;
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        long L = in.nextInt() + 1;
        len = new long[N + 1];
        dp = new long[N + 1];
        ind = new int[N + 1];
        for (int i = 1; i <= N; i++) {
            len[i] = in.nextLong() + len[i - 1] + 1;
        }
        int l = 0;
        int r = 0;
        for (int i = 1; i <= N; i++) {
            while (l < r && slope(ind[l], ind[l + 1]) < len[i] - L) {
                l++;
            }
            dp[i] = dp[ind[l]] + (len[i] - len[ind[l]] - L) * (len[i] - len[ind[l]] - L);
            while (l < r && slope(ind[r - 1], ind[r]) > slope(ind[r], i)) {
                r--;
            }
            ind[++r] = i;
        }
        out.println(dp[N]);
        out.close();
    }
    
    public static double slope(int i, int j) {
        return ((double) (dp[j] - dp[i] + len[j] * len[j] - len[i] * len[i])) / ((double) (2 * (len[j] - len[i])));
    }
}
