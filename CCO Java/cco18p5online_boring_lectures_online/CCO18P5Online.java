import java.io.*;
import java.math.*;
import java.util.*;

public class CCO18P5Online {
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
    
    static int N, K, Q;
    static int[] A, T, IND;
    
    static void updateT(int i, int v) {
        for (T[i += N] = v; (i >>= 1) > 0;) T[i] = Math.max(T[i << 1], T[i << 1 | 1]);
    }
    
    static void updateIND(int i) {
        for (i += N; (i >>= 1) > 0;) IND[i] = A[IND[i << 1]] > A[IND[i << 1 | 1]] ? IND[i << 1] : IND[i << 1 | 1];
    }
    
    static int queryIND(int l, int r) {
        if (l > r) return N;
        int ql = N;
        int qr = N;
        for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
            if ((l & 1) == 1) {
                ql = A[ql] > A[IND[l]] ? ql : IND[l];
                l++;
            }
            if ((r & 1) == 0) {
                qr = A[IND[r]] > A[qr] ? IND[r] : qr;
                r--;
            }
        }
        return A[ql] > A[qr] ? ql : qr;
    }
    
    public static void run(int testCaseNum) throws Exception {
        N = in.nextInt();
        K = in.nextInt();
        Q = in.nextInt();
        A = new int[N + 1];
        T = new int[2 * N];
        IND = new int[2 * N];
        for (int i = 0; i < N; i++) {
            A[i] = in.nextInt();
            IND[N + i] = i;
            T[i] = 0;
        }
        A[N] = 0;
        for (int i = N - 1; i >= 0; i--) IND[i] = A[IND[i << 1]] > A[IND[i << 1 | 1]] ? IND[i << 1] : IND[i << 1 | 1];
        int l, r, l2, r2, j, x;
        for (int i = 0; i < N; i++) {
            l = queryIND(Math.max(0, i - K + 1), i - 1);
            r = queryIND(i + 1, Math.min(i + K - 1, N - 1));
            if (A[i] >= A[l] && A[i] > A[r]) updateT(i, A[i] + Math.max(A[l], A[r]));
        }
        out.println(T[1]);
        for (int i = 0; i < Q; i++) {
            j = in.nextInt();
            x = in.nextInt();
            A[--j] = x;
            updateIND(j);
            l = queryIND(Math.max(0, j - K + 1), j - 1);
            r = queryIND(j + 1, Math.min(j + K - 1, N - 1));
            if (A[j] >= A[l] && A[j] > A[r]) updateT(j, A[j] + Math.max(A[l], A[r]));
            else {
                updateT(j, 0);
                if (l < N) {
                    l2 = queryIND(Math.max(0, l - K + 1), l - 1);
                    r2 = queryIND(l + 1, Math.min(l + K - 1, N - 1));
                    if (A[l] >= A[l2] && A[l] > A[r2]) updateT(l, A[l] + Math.max(A[l2], A[r2]));
                }
                if (r < N) {
                    l2 = queryIND(Math.max(0, r - K + 1), r - 1);
                    r2 = queryIND(r + 1, Math.min(r + K - 1, N - 1));
                    if (A[r] >= A[l2] && A[r] > A[r2]) updateT(r, A[r] + Math.max(A[l2], A[r2]));
                }
            }
            out.println(T[1]);
        }
    }
}
