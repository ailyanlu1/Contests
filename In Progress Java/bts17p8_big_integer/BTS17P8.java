import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class BTS17P8 {
    private static BTS17P8 o = new BTS17P8();
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
    
    public class FenwickTreeRangePoint {

        private int[] array; // 1-indexed array, In this array We save cumulative information to perform efficient range queries and updates

        public FenwickTreeRangePoint(int size) {
            array = new int[size + 1];
        }

        /**
         * Value at index {@code ind}.
         * <p>
         * Time-Complexity:    O(log(n))
         *
         * @param  ind index
         * @return sum
         */
        public int getValue(int ind) {
            int sum = 0;
            for (int x = ind; x > 0; x -= (x & -x)) {
                sum += array[x];
            }
            return sum;
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
            for (int x = ind; x < array.length; x += (x & -x)) {
                array[x] += value;
            }
        }
        
        /**
         * Update the array between a and b.
         * ind is 1-indexed
         * <p>
         * Time-Complexity:    O(log(n))
         *
         * @param  ind   index
         * @param  value value
         */
        public void update(int a, int b, int value) {
            update(a, value);
            update(b + 1, -value);
        }

        public int size() {
            return array.length - 1;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        char[] S = in.next().toCharArray();
        if (N <= 8) {
            String curStr = "0";
            BigInteger total = BigInteger.ZERO;
            for (int i = 0; i < N; i++) {
                if (S[i] == '-') curStr = curStr.substring(0, curStr.length() - 1);
                else curStr += S[i];
                total = total.add(new BigInteger(curStr));
            }
            out.println(total);
        } else {
            boolean noRemove = true;
            for (int i = 0; i < N; i++) {
                if (S[i] == '-') {
                    noRemove = false;
                    break;
                }
            }
            if (noRemove) {
                FenwickTreeRangePoint ft = o.new FenwickTreeRangePoint(N);
                for (int i = 0; i < N; i++) {
                    ft.update(i + 1, N, S[i] - '0');
                }
                int carry = 0, val;
                StringBuilder s = new StringBuilder();
                for (int i = N; i > 0; i--) {
                    val = ft.getValue(i);
                    s.append((val + carry) % 10);
                    carry = (val + carry) / 10;
                }
                s.append(carry);
                out.println(s.reverse());
            } else {
                int digitLoc = -1;
                int digit = 0;
                int len = 1;
                FenwickTreeRangePoint ft = o.new FenwickTreeRangePoint(N);
                for (int i = 0; i < N; i++) {
                    if (S[i] == '-') {
                        len--;
                        if (digitLoc >= len) digitLoc = -1;
                        else {
                            ft.update(len - digitLoc, len - digitLoc, digit);
                        }
                    } else if (S[i] != '0') {
                        digitLoc = len;
                        digit = S[i] - '0';
                        len++;
                        ft.update(len - digitLoc, len - digitLoc, digit);
                    } else {
                        len++;
                        if (digitLoc != -1) ft.update(len - digitLoc, len - digitLoc, digit);
                    }
                }
                int carry = 0, val;
                StringBuilder s = new StringBuilder();
                for (int i = 1; i <= N; i++) {
                    val = ft.getValue(i);
                    s.append((val + carry) % 10);
                    carry = (val + carry) / 10;
                }
                s.append(carry);
                out.println(s.reverse());
            }
        }
        out.close();
    }
}
