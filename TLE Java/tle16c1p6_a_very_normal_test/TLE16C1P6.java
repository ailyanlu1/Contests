package tle16c1p6_a_very_normal_test;

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

public class TLE16C1P6 {
    private static TLE16C1P6 o = new TLE16C1P6();
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
    
    public static class XorSat {
        // Gaussian elimination with partial pivoting
        public static boolean[] solve(boolean[][] A, boolean[] b) {
            int n = b.length;
            for (int p = 0; p < n; p++) {
                // find pivot row and swap
                int m = p;
                for (int i = 0; i < p; i++) {
                    int j = i;
                    while (j < n && !A[i][j]) {
                        j++;
                    }
                    if (j == p) m = i;
                }
                for (int i = p + 1; i < n; i++) {
                    if (A[i][p]) m = i;
                }
                if (!A[m][p]) continue;
                boolean[] tempA = A[p];
                A[p] = A[m];
                A[m] = tempA;
                boolean tempB = b[p];
                b[p] = b[m];
                b[m] = tempB;
                // pivot within A and b
                for (int i = 0; i < n; i++) {
                    if (p == i || !A[i][p]) continue;
                    b[i] ^= b[p];
                    for (int j = p; j < n; j++) {
                        A[i][j] ^= A[p][j];
                    }
                }
            }
            // back substitution
            for (int i = n - 1; i >= 0; i--) {
                if (!A[i][i] && b[i]) throw new ArithmeticException("Matrix has no solution");
                if (!b[i]) continue;
                for (int j = i - 1; j >= 0; j--) {
                    b[j] ^= A[j][i];
                    A[j][i] = false;
                }
            }
            return b;
        }
    }
    
    private static Reader in = o.new Reader(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    
    public static void main(String[] args) throws IOException {
        int N = in.nextInt();
        boolean[][] A = new boolean[N][N];
        boolean[] b = new boolean[N];
        for (int i = 0; i < N; i++) {
            String line = in.nextLine().trim();
            if (line.charAt(0) == '!') {
                int p = Integer.parseInt(line.substring(1)) - 1;
                A[i][p] ^= true;
            } else {
                int ind = line.indexOf('=');
                int p = Integer.parseInt(line.substring(0, ind)) - 1;
                int q = Integer.parseInt(line.substring(ind + 2)) - 1;
                A[i][p] ^= true;
                A[i][q] ^= true;
            }
            A[i][i] ^= true;
            b[i] = true;
        }
        try {
            boolean[] x = XorSat.solve(A, b);
            for (int i = 0; i < N; i++) {
               out.println(x[i]);
            }
        } catch (ArithmeticException e) {
            out.println("No perfect solution found");
        }
        out.close();
    }
}
