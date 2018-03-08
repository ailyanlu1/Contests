import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class CCO14P5 {
    private static CCO14P5 o = new CCO14P5();
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
    
    public class FenwickTree {

        long[] array; // 1-indexed array, In this array We save cumulative information to perform efficient range queries and updates

        public FenwickTree(int size) {
            array = new long[size + 1];
        }

        /**
         * Range Sum query from 1 to ind
         * ind is 1-indexed
         * <p>
         * Time-Complexity:    O(log(n))
         *
         * @param  ind index
         * @return sum
         */
        public long rsq(int ind) {
            // assert ind > 0;
            long sum = 0;
            for (int x = ind; x > 0; x -= (x & -x)) {
                sum += array[x];
            }
            return sum;
        }

        /**
         * Range Sum Query from a to b.
         * Search for the sum from array index from a to b
         * a and b are 1-indexed
         * <p>
         * Time-Complexity:    O(log(n))
         *
         * @param  a left index
         * @param  b right index
         * @return sum
         */
        public long rsq(int a, int b) {
            // assert b >= a && a > 0 && b > 0;
            return rsq(b) - rsq(a - 1);
        }

        /**
         * Update the array at ind and all the affected regions above ind.
         * ind is 1-indexed
         * <p>
         * Time-Complexity:    O(log(n))
         *
         * @param  ind   index
         * @param  value value
         */
        public void update(int ind, int value) {
            // assert ind > 0;
            for (int x = ind; x < array.length; x += (x & -x)) {
                array[x] += value;
            }
        }

        public int size() {
            return array.length - 1;
        }
    }
    
    public class ComparablePair<Item extends Comparable<Item>, Item2 extends Comparable<Item2>> implements Comparable<ComparablePair<Item, Item2>> {
        public Item first;
        public Item2 second;

        public ComparablePair(Item first, Item2 second) {
            this.first = first;
            this.second = second;
        }
        
        @Override
        public int hashCode() {
            return 31 * first.hashCode() + second.hashCode();
        }

        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof ComparablePair)) return false;
            ComparablePair p = (ComparablePair) o;
            return p.first.equals(first) && p.second.equals(second);
        }

        @Override
        public int compareTo(ComparablePair<Item, Item2> p) {
            if (first.compareTo(p.first) != 0) return first.compareTo(p.first);
            return (second.compareTo(p.second));
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    private static final int MAXC = 6;
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        int M = in.nextInt();
        int A = in.nextInt();
        int B = in.nextInt();
        FenwickTree ft0 = o.new FenwickTree(N * MAXC);
        FenwickTree ft1 = o.new FenwickTree(N * MAXC);
        boolean[][] room = new boolean[N + 1][MAXC + 1];
        ComparablePair<Integer, Integer>[] seat = new ComparablePair[M + 1];
        ComparablePair<Long, Long>[] cost = new ComparablePair[M + 1];
        ComparablePair<Long, Integer>[] people = new ComparablePair[M + 1];
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j <= MAXC; j++) {
                room[i][j] = true;
            }
        }
        for (int i = 1; i <= N; i++) {
            ft0.update(i, 1);
            ft1.update(i, 1);
        }
        for (int i = 1; i <= M; i++) {
            String str = in.next();
            seat[i] = o.new ComparablePair<Integer, Integer>(Integer.parseInt(str.substring(0, str.length() - 1)),
                str.charAt(str.length() - 1) - 'A' + 1);
        }
        for (int i = 1; i <= M; i++) {
            long count = 0;
            room[seat[i].first][seat[i].second] = false;
            if (seat[i].second == 3) ft0.update(seat[i].first, -1);
            else if (seat[i].second == 4) ft1.update(seat[i].first, -1);
            if (seat[i].second <= 3) {
                for (int j = seat[i].second + 1; j < 3; j++) {
                    count += room[seat[i].first][j] ? 1 : 0;
                }
            } else {
                for (int j = seat[i].second - 1; j > 4; j--) {
                    count += room[seat[i].first][j] ? 1 : 0;
                }
            }
            cost[i] = o.new ComparablePair<Long, Long>((long) (A) * (count + ft0.rsq(seat[i].first) + ft1.rsq(seat[i].first)),
                (long) (A) * (count + ft0.rsq(seat[i].first, N) + ft1.rsq(seat[i].first, N)));
            people[i] = o.new ComparablePair<Long, Integer>(cost[i].first - cost[i].second, i);
        }
        Arrays.sort(people, 1, M + 1);
        long[][] psa = new long[2][M + 1];
        for (int i = 1; i <= M; i++) {
            psa[0][i] = psa[0][i - 1] + cost[people[i].second].first;
            psa[1][i] = psa[1][i - 1] + cost[people[i].second].second;
        }
        long ans = Long.MAX_VALUE;
        for (int i = 0; i <= M; i++) {
            ans = Math.min(ans, psa[0][i] + psa[1][M] - psa[1][i] + (long) (B) * i * (i - 1) / 2 + (long) (B) * (M - i) * (M - i - 1) / 2);
        }
        out.println(ans);
        out.close();
    }
}
