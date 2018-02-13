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

public class CCC10S5_Node {
    private static CCC10S5_Node o = new CCC10S5_Node();
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
    
    private static class Node {
        Node left, right;
        int val;
        int[] dp;
        int[] dpl;
        int[] dpr;
    }
    
    private static char[] line;
    private static int cInd = 0;
    private static int X;
    private static Node root;
    
    public static void main(String[] args) throws IOException {
        line = (in.nextLine().trim() + " ").toCharArray();
        root = build();
        X = in.nextInt();
        solve(root);
        out.println(root.dp[X]);
        out.close();
    }
    
    private static Node build() throws IOException {
        Node cur = new Node();
        while (line[cInd] == ' ' || line[cInd] == ')') {
            cInd++;
        }
        char c = line[cInd++];
        if (c == '(') {
            cur.left = build();
            cur.right = build();
        } else {
            int val = c - '0';
            while (line[cInd] >= '0' && line[cInd] <= '9') {
                val = 10 * val + (line[cInd++] - '0');
            }
            cur.val = val;
        }
        return cur;
    }
    
    private static void solve(Node cur) {
        if (cur.val == 0) {
            solve(cur.left);
            solve(cur.right);
            cur.dp = new int[X + 1];
            cur.dpl = new int[X + 1];
            cur.dpr = new int[X + 1];
            for (int i = 0; i <= X; i++) {
                for (int j = 0; j <= i; j++) {
                    cur.dpl[i] = Math.max(cur.dpl[i], Math.min(cur.left.dp[i - j], (1 + j) *(1 + j)));
                }
            }
            for (int i = 0; i <= X; i++) {
                for (int j = 0; j <= i; j++) {
                    cur.dpr[i] = Math.max(cur.dpr[i], Math.min(cur.right.dp[i - j], (1 + j) *(1 + j)));
                }
            }
            for (int i = 0; i <= X; i++) {
                for (int j = 0; j <= i; j++) {
                    cur.dp[i] = Math.max(cur.dp[i], cur.dpl[j] + cur.dpr[i - j]);
                }
            }
        } else {
            cur.dp = new int[X + 1];
            for (int i = 0; i <= X; i++) {
                cur.dp[i] = cur.val + i;
            }
        }
    }
}
