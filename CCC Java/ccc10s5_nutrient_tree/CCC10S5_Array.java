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

public class CCC10S5_Array {
    private static CCC10S5_Array o = new CCC10S5_Array();
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
    
    private static char[] line;
    private static int cInd = 0;
    private static int X;
    private static int[] tree;
    private static int[][][] dp;
    
    public static void main(String[] args) throws IOException {
        line = (in.nextLine().trim() + " ").toCharArray();
        tree = new int[line.length];
        build(1);
        X = in.nextInt();
        dp = new int[3][tree.length][X + 1];
        solve(1);
        out.println(dp[0][1][X]);
        out.close();
    }
    
    private static void build(int cur) throws IOException {
        while (line[cInd] == ' ' || line[cInd] == ')') {
            cInd++;
        }
        char c = line[cInd++];
        if (c == '(') {
            build(cur * 2);
            build(cur * 2 + 1);
        } else {
            int val = c - '0';
            while (line[cInd] >= '0' && line[cInd] <= '9') {
                val = 10 * val + (line[cInd++] - '0');
            }
            tree[cur] = val;
        }
    }
    
    private static void solve(int cur) {
        if (tree[cur] == 0) {
            solve(cur * 2);
            solve(cur * 2 + 1);
            for (int i = 0; i <= X; i++) {
                for (int j = 0; j <= i; j++) {
                    dp[1][cur][i] = Math.max(dp[1][cur][i], Math.min(dp[0][cur * 2][i - j], (1 + j) *(1 + j)));
                }
            }
            for (int i = 0; i <= X; i++) {
                for (int j = 0; j <= i; j++) {
                    dp[2][cur][i] = Math.max(dp[2][cur][i], Math.min(dp[0][cur * 2 + 1][i - j], (1 + j) *(1 + j)));
                }
            }
            for (int i = 0; i <= X; i++) {
                for (int j = 0; j <= i; j++) {
                    dp[0][cur][i] = Math.max(dp[0][cur][i], dp[1][cur][j] + dp[2][cur][i - j]);
                }
            }
        } else {
            for (int i = 0; i <= X; i++) {
                dp[0][cur][i] = tree[cur] + i;
            }
        }
    }
}
