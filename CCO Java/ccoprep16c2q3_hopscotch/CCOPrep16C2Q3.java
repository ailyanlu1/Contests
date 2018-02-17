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

public class CCOPrep16C2Q3 {
    private static CCOPrep16C2Q3 o = new CCOPrep16C2Q3();
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
    private static int N, SQRT_N;
    private static int[] pow, hop, turns;
    
    public static void main(String[] args) throws IOException {
        N = in.nextInt();
        SQRT_N = (int) Math.ceil(Math.sqrt(N));
        pow = new int[N];
        hop = new int[N];
        turns = new int[N];
        for (int i = 0; i < N; i++) {
            pow[i] = in.nextInt();
        }
        for (int i = 1; i <= SQRT_N; i++) {
            update(i);
        }
        int Q = in.nextInt();
        for (int i = 0; i < Q; i++) {
            int o = in.nextInt();
            if (o == 1) {
                int x = in.nextInt();
                int ans = 0;
                while (x != N) {
                    ans += turns[x];
                    x = hop[x];
                }
                out.println(ans);
            } else /*if (o == 2)*/{
                int x = in.nextInt();
                int v = in.nextInt();
                pow[x] = v;
                update((int) Math.ceil((double) x / SQRT_N));
            }
        }
        out.close();
    }
    
    private static void update(int square) {
        for (int i = Math.min(SQRT_N * square, N - 1); i >= Math.max(SQRT_N * (square - 1), 0); i--) {
            if (i + pow[i] >= Math.min(SQRT_N * square, N)) {
                hop[i] = Math.min(i + pow[i], N);
                turns[i] = 1;
            } else {
                hop[i] = hop[i + pow[i]];
                turns[i] = turns[i + pow[i]] + 1;
            }
        }
    }
}
