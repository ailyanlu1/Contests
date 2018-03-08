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

public class CCOPrep2P1 {
    private static CCOPrep2P1 o = new CCOPrep2P1();
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
    private static long M;
    
    public static void main(String[] args) throws IOException {
        long N = in.nextLong();
        M = in.nextLong();
        long[] a = {0, 1, 1};
        for (long i = 10, j = 1; j <= N; j = i, i *= 10) {
            long seg = Math.min(N, j * 10 - 1);
            long[][] mat = {{i % M, 0, 0}, {1, 1, 0}, {0, 1, 1}};
            mat = pow(mat, seg - j + 1);
            a = multiply(a, mat);
        }
        out.println((long) a[0]);
        out.close();
    }
    
    // vector-matrix multiplication (y = x^T A)
    public static long[] multiply(long[] x, long[][] a) {
        int m = a.length;
        int n = a[0].length;
        if (x.length != m)
            throw new RuntimeException("Illegal matrix dimensions.");
        long[] y = new long[n];
        for (int j = 0; j < n; j++)
            for (int i = 0; i < m; i++)
                y[j] = (y[j] + a[i][j] * x[i] % M) % M;
        return y;
    }
    
    // return c = a * b
    public static long[][] multiply(long[][] a, long[][] b) {
        int m1 = a.length;
        int n1 = a[0].length;
        int m2 = b.length;
        int n2 = b[0].length;
        if (n1 != m2)
            throw new RuntimeException("Illegal matrix dimensions.");
        long[][] c = new long[m1][n2];
        for (int i = 0; i < m1; i++)
            for (int j = 0; j < n2; j++)
                for (int k = 0; k < n1; k++)
                    c[i][j] = (c[i][j] + a[i][k] * b[k][j] % M) % M;
        return c;
    }
    
    // matrix power (y = a^x)
    public static long[][] pow(long[][] a, long x) {
        int m = a.length;
        int n = a[0].length;
        long[][] y = new long[m][n];
        boolean flag = false;
        while (x > 0) {
            if (x % 2 == 1) {
                if (!flag) {
                    y = a;
                    flag = true;
                } else {
                    y = multiply(y, a);
                }
            }
            a = multiply(a, a);
            x /= 2;
        }
        return y;
    }
}
