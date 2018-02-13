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

public class CCC10S3 {
    private static CCC10S3 o = new CCC10S3();
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
    private static int[] houses;
    private static int H;
    
    public static void main(String[] args) throws IOException {
        H = in.nextInt();
        houses = new int[H * 2];
        for (int i = 0; i < H; i++) {
            houses[i] = in.nextInt();
        }
        Arrays.sort(houses, 0, H);
        for (int i = 0; i < H; i++) {
            houses[i + H] = houses[i] + 1000000;
        }
        int K = in.nextInt();
        int lo = 0;
        int hi = 1000000;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (calc(mid) > K) lo = mid + 1;
            else hi = mid;
        }
        out.println(lo);
        out.close();
    }
    
    private static int calc(int len) {
        int min = Integer.MAX_VALUE;
        for (int i = 0; i < H; i++) {
            int cur = i;
            int h = 1;
            for (int j = i; j < H + i; j++) {
                if (houses[j] - houses[cur] > 2 * len) {
                    cur = j;
                    h++;
                }
            }
            min = Math.min(min, h);
        }
        return min;
    }
}
