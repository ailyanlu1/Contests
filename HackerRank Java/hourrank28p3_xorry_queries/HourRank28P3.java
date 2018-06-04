import java.io.*;
import java.math.*;
import java.util.*;

public class HourRank28P3 {
    public static class Reader {
        private final int BUFFER_SIZE = 1 << 16;
        private int LENGTH = -1;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;

        public Reader(InputStream inputStream) {
            din = new DataInputStream(inputStream);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public Reader(String file_name) throws IOException {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public int nextInt() throws IOException {
            int ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg) return -ret;
            return ret;
        }

        public long nextLong() throws IOException {
            long ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg) return -ret;
            return ret;
        }
        
        public double nextDouble() throws IOException {
            double ret = 0, div = 1;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (c == '.') while ((c = read()) >= '0' && c <= '9') ret += (c - '0') / (div *= 10);
            if (neg) return -ret;
            return ret;
        }

        public char nextChar() throws IOException {
            byte c;
            do {
                c = read();
            } while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1);
            return (char) c;
        }

        public String next() throws IOException {
            byte[] buf = new byte[LENGTH];
            int cnt = 0, c;
            do {
                c = read();
            } while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1);
            buf[cnt++] = (byte) c;
            while ((c = read()) != -1) {
                if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1) break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }
        
        public String nextLine() throws IOException {
            byte[] buf = new byte[LENGTH];
            int cnt = 0, c;
            do {
                c = read();
            } while (c == ' ' || c == '\n' || c == '\r' || c == -1);
            buf[cnt++] = (byte) c;
            while ((c = read()) != -1) {
                if (c == '\n' || c == '\r' || c == -1) break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }
        
        public void setLength(int length) {
            LENGTH = length;
        }

        private void fillBuffer() throws IOException {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1) buffer[0] = -1;
        }

        private byte read() throws IOException {
            if (bufferPointer == bytesRead) fillBuffer();
            return buffer[bufferPointer++];
        }

        public void close() throws IOException {
            if (din == null) return;
            din.close();
        }
    }
    
    private static Reader in;
    private static PrintWriter out;
    
    private static int NUM_OF_TEST_CASES = 1; // TODO CHANGE NUMBER OF TEST CASES
    
    // TODO CHANGE FILE NAMES
    private static final String INPUT_FILE_NAME = "input.txt";
    private static final String OUTPUT_FILE_NAME = "output.txt";
    
    private static boolean stdIn = true;
    private static boolean stdOut = true;
    private static boolean crash = true;
    private static boolean flush = false;
    
    public static void main(String[] args) throws Exception {
        if (stdIn) in = new Reader(System.in);
        else in = new Reader(INPUT_FILE_NAME);
        if (stdOut) out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        else out = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE_NAME)));
        for (int i = 1; i <= NUM_OF_TEST_CASES; i++) {
            try {
                run(i);
            } catch (Exception e) {
                out.println("Exception thrown on test case " + i);
                e.printStackTrace(out);
                out.flush();
                if (crash) throw new Exception();
            }
            if (flush) out.flush();
        }
        in.close();
        out.close();
    }

    static int N, M, K, H, P;
    static int[] A;
    static int[][] B, T, L;
    static final int MAXBITS = 18;

    static void apply(int t, int i, int k) {
        T[t][i] = k - T[t][i];
        if (i < K) L[t][i] ^= 1;
    }

    static void pushup(int t, int i) {
        for (int k = 2; i > 1; k <<= 1) {
            i >>= 1;
            T[t][i] = L[t][i] == 0 ? T[t][i << 1] + T[t][i << 1 | 1] : k - (T[t][i << 1] + T[t][i << 1 | 1]);
        }
    }

    static void propagate(int t, int i) {
        for (int h = H, k = 1 << (H - 1); h > 0; h--, k >>= 1) {
            int ii = i >> h;
            if (L[t][ii] == 1) {
                apply(t, ii << 1, k);
                apply(t, ii << 1 | 1, k);
                L[t][ii] = 0;
            }
        }
    }

    static void update(int t, int l, int r) {
        l += K - 1;
        r += K - 1;
        propagate(t, l);
        propagate(t, r);
        int l0 = l, r0 = r, k = 1;
        for (; l <= r; l >>= 1, r >>= 1, k <<= 1) {
            if ((l & 1) == 1) apply(t, l++, k);
            if ((r & 1) == 0) apply(t, r--, k);
        }
        pushup(t, l0);
        pushup(t, r0);
    }

    static int query(int t, int l, int r) {
        l += K - 1;
        r += K - 1;
        propagate(t, l);
        propagate(t, r);
        int q = 0;
        for (; l <= r; l >>= 1, r >>= 1) {
            if ((l & 1) == 1) q += T[t][l++];
            if ((r & 1) == 0) q += T[t][r--];
        }
        return q;
    }

    static void build(int t) {
        for (int i = 0; i < K; i++) T[t][K + i] = B[t][i + 1];
        for (int i = K - 1; i > 0; i--) T[t][i] = T[t][i << 1] + T[t][i << 1 | 1];
    }
    
    public static void run(int testCaseNum) throws Exception {
        N = in.nextInt();
        M = in.nextInt();
        P = in.nextInt();
        K = N - P + 1;
        for (int i = 1; i <= K; H++) i <<= 1;
        A = new int[N + 1];
        B = new int[MAXBITS][K + 1];
        T = new int[MAXBITS][2 * K];
        L = new int[MAXBITS][K];
        for (int i = 1; i <= N; i++) A[i] = in.nextInt();
        int curXor = 0;
        for (int i = 1; i < P; i++) curXor ^= A[i];
        for (int i = 1; i <= K; i++) {
            curXor ^= A[i - 1] ^= A[i + P - 1];
            for (int k = 0; k < MAXBITS; k++) B[k][i] = (curXor >> k) & 1;
        }
        for (int i = 0; i < MAXBITS; i++) build(i);
        for (int m = 0; m < M; m++) {
            int t = in.nextInt();
            if (t == 1) {
                int i = in.nextInt(), x = in.nextInt();
                int l = Math.max(1, i - P + 1), r = Math.min(i, K);
                for (int j = 0; j < MAXBITS; j++) if (((x >> j) & 1) == 1) update(j, l, r);
            } else {
                int l = in.nextInt(), r = Math.min(in.nextInt(), K);
                if (l > K) out.println(0);
                else {
                    long ans = 0;
                    for (int j = 0; j < MAXBITS; j++) ans += (1L << j) * query(j, l, r);
                    out.println(ans);
                }
            }
        }
    }
}
