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

public class TLE16C8P3 {
    private static TLE16C8P3 o = new TLE16C8P3();
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
    
    public static class BinarySearch {

        /**
         * This class should not be instantiated.
         */
        private BinarySearch() { }

        /**
         * Returns the index of the specified key in the specified array.
         *
         * @param  a the array, must be sorted in ascending order
         * @param  start the inclusive start index
         * @return index of key in array {@code a} if present; {@code -1} otherwise
         */
        public static int indexOf(Comparable[] a, Comparable key) {
            return indexOf(a, 0, a.length, key);
        }
        
        /**
         * Returns the index of the specified key in the specified array between indices {@code start} (inclusive)
         * and {@code end} (exclusive).
         *
         * @param  a the array, must be sorted in ascending order
         * @param  start the inclusive start index
         * @param  end the exclusive end index
         * @param  key the search key
         * @return index of key in array {@code a} if present; {@code -1} otherwise
         */
        public static int indexOf(Comparable[] a, int start, int end, Comparable key) {
            int lo = start;
            int hi = end - 1;
            while (lo <= hi) {
                // Key is in a[lo..hi] or not present.
                int mid = lo + (hi - lo) / 2;
                int cmp = key.compareTo(a[mid]);
                if      (cmp < 0) hi = mid - 1;
                else if (cmp > 0) lo = mid + 1;
                else return mid;
            }
            return -1;
        }
        
        /**
         * Returns the index of the first element that is not less than the key 
         * in the specified array.
         *
         * @param  a the array, must be sorted in ascending order
         * @param  key the search key
         * @return index of first element not less than key in array {@code a};
         * {@code a.length} if key is larger than the largest element
         */
        public static int lowerBound(Comparable[] a, Comparable key) {
            return lowerBound(a, 0, a.length, key);
        }
        
        /**
         * Returns the index of the first element that is not less than the key 
         * in the specified array between indices {@code start} (inclusive)
         * and {@code end} (exclusive).
         *
         * @param  a the array, must be sorted in ascending order
         * @param  start the inclusive start index
         * @param  end the exclusive end index
         * @param  key the search key
         * @return index of first element not less than key in array {@code a};
         * {@code end} if key is larger than the largest element
         */
        public static int lowerBound(Comparable[] a, int start, int end, Comparable key) {
            int lo = start;
            int hi = end;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                int cmp = key.compareTo(a[mid]);
                if (cmp <= 0) hi = mid;
                else lo = mid + 1;
            }
            return lo;
        }
        
        /**
         * Returns the index of the first element that is greater than the key 
         * in the specified array.
         *
         * @param  a the array, must be sorted in ascending order
         * @param  key the search key
         * @return index of first element greater than key in array {@code a};
         * {@code a.length} if key is larger than or equal to the largest element
         */
        public static int upperBound(Comparable[] a, Comparable key) {
            return upperBound(a, 0, a.length, key);
        }
        
        /**
         * Returns the index of the first element that is greater than the key 
         * in the specified array between indices {@code start} (inclusive)
         * and {@code end} (exclusive).
         *
         * @param  a the array, must be sorted in ascending order
         * @param  start the inclusive start index
         * @param  end the exclusive end index
         * @param  key the search key
         * @return index of first element greater than key in array {@code a};
         * {@code end} if key is larger than or equal to the largest element
         */
        public static int upperBound(Comparable[] a, int start, int end, Comparable key) {
            int lo = start;
            int hi = end;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                int cmp = key.compareTo(a[mid]);
                if (cmp >= 0) lo = mid + 1;
                else hi = mid;
            }
            return lo;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    private static long[] dp = new long[128];
    private static Long[] psa = new Long[128];
    
    private static void pre() {
        psa[0] = psa[1] = dp[0] = dp[1] = 0L;
        psa[2] = dp[2] = dp[3] = 1L;
        psa[3] = 2L;
        for (int i = 4; i < 128; i++) {
            dp[i] = dp[i - 2] + dp[i - 3];
            psa[i] = psa[i - 1] + dp[i];
        }
    }
    
    public static void main(String[] args) throws IOException {
        pre();
        int T = in.nextInt();
        for (int i = 1; i <= T; i++) {
            run(i);
        }
        out.close();
    }
    
    public static void run(int testCaseNum) throws IOException {
        long N = in.nextLong();
        int d = BinarySearch.lowerBound(psa, N);
        N -= psa[d - 1] + 1;
        while (d > 0) {
            if (d == 2) {
                out.print(69);
                d -= 2;
            } else if (d == 3) {
                out.print(420);
                d -= 3;
            } else if (N < dp[d - 3]) {
                out.print(420);
                d -= 3;
            } else {
                out.print(69);
                N -= dp[d - 3];
                d -= 2;
            }
        }
        out.println();
    }
}