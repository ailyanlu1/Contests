package coci14c7p3_acm;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Iterator;
import java.util.StringTokenizer;

public class COCI14C7P3 {
    private static COCI14C7P3 o = new COCI14C7P3();
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
    
    public class JohnsonTrotterPermIterator implements Iterator<int[]> {
        private int[] next = null;
        private final int n;
        private int[] perm;
        private int[] dirs;

        public JohnsonTrotterPermIterator(int size) {
            n = size;
            if (n <= 0) {
                perm = (dirs = null);
            } else {
                perm = new int[n];
                dirs = new int[n];
                for (int i = 0; i < n; i++) {
                    perm[i] = i;
                    dirs[i] = -1;
                }
                dirs[0] = 0;
            }
            next = perm;
        }

        @Override
        public int[] next() {
            int[] r = makeNext();
            next = null;
            return r;
        }

        @Override
        public boolean hasNext() {
            return (makeNext() != null);
        }

        private int[] makeNext() {
            if (next != null)
                return next;
            if (perm == null)
                return null;

            // find the largest element with != 0 direction
            int i = -1, e = -1;
            for (int j = 0; j < n; j++)
                if ((dirs[j] != 0) && (perm[j] > e)) {
                    e = perm[j];
                    i = j;
                }

            if (i == -1) // no such element -> no more premutations
                return (next = (perm = (dirs = null))); // no more permutations

            // swap with the element in its direction
            int k = i + dirs[i];
            swap(i, k, dirs);
            swap(i, k, perm);
            // if it's at the start/end or the next element in the direction
            // is greater, reset its direction.
            if ((k == 0) || (k == n - 1) || (perm[k + dirs[k]] > e))
                dirs[k] = 0;

            // set directions to all greater elements
            for (int j = 0; j < n; j++)
                if (perm[j] > e)
                    dirs[j] = (j < k) ? +1 : -1;

            return (next = perm);
        }

        private void swap(int i, int j, int[] arr) {
            int v = arr[i];
            arr[i] = arr[j];
            arr[j] = v;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    private static final int INT_INF = 0x3f3f3f3f;
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int[][] tasks = new int[3][N];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < N; j++) {
                tasks[i][j] = in.nextInt();
            }
        }
        JohnsonTrotterPermIterator iter = o.new JohnsonTrotterPermIterator(3);
        int ans = Integer.MAX_VALUE;
        while (iter.hasNext()) {
            int[] order = iter.next();
            int[] a = tasks[order[0]];
            int[] b = tasks[order[1]];
            int[] c = tasks[order[2]];
            int[][] dp = new int[N][3];
            dp[0][0] = a[0];
            dp[0][1] = dp[0][2] = dp[1][2] = INT_INF;
            for (int i = 1; i < N; i++) {
                dp[i][0] = a[i] + dp[i - 1][0];
                dp[i][1] = b[i] + Math.min(dp[i - 1][0], dp[i - 1][1]);
                dp[i][2] = c[i] + Math.min(dp[i - 1][1], dp[i - 1][2]);
            }
            ans = Math.min(ans, dp[N - 1][2]);
        }
        out.println(ans);
        out.close();
    }
}
