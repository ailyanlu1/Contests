// http://codeforces.com/contest/1000/problem/F
import java.io.*;
import java.math.*;
import java.util.*;

public class EduRound46F {
    public static class Reader {
        private final int BUFFER_SIZE = 1 << 12;
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
            byte c;
            do {
                c = read();
            } while (c <= ' ');
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0');
            if (neg) return -ret;
            return ret;
        }

        public long nextLong() throws IOException {
            long ret = 0;
            byte c;
            do {
                c = read();
            } while (c <= ' ');
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0');
            if (neg) return -ret;
            return ret;
        }

        public double nextDouble() throws IOException {
            double ret = 0, div = 1;
            byte c;
            do {
                c = read();
            } while (c <= ' ');
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0');
            if (c == '.') while ((c = read()) >= '0') ret += (c - '0') / (div *= 10);
            if (neg) return -ret;
            return ret;
        }

        public char nextChar() throws IOException {
            byte c;
            do {
                c = read();
            } while (c <= ' ');
            return (char) c;
        }

        public String next() throws IOException {
            byte[] buf = new byte[LENGTH];
            int cnt = 0, c;
            do {
                c = read();
            } while (c <= ' ');
            do {
                buf[cnt++] = (byte) c;
            } while ((c = read()) > ' ');
            return new String(buf, 0, cnt);
        }

        public String nextLine() throws IOException {
            byte[] buf = new byte[LENGTH];
            int cnt = 0, c;
            do {
                c = read();
            } while (c <= ' ');
            do {
                buf[cnt++] = (byte) c;
            } while ((c = read()) >= ' ');
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
    
    static final int MAXA = 500005;
    static final int INF = 0x3f3f3f3f;
    static int N, Q;
    static int[] A, ind, ans;
    static int[][] T;
    static ArrayList<int[]>[] queries;

    static void merge(int i, int j, int k) {
        if (T[j][0] < T[k][0]) {
            T[i][0] = T[j][0];
            T[i][1] = T[j][1];
        } else {
            T[i][0] = T[k][0];
            T[i][1] = T[k][1];
        }
    }

    static void build() {
        T = new int[2 * N][2];
        for (int i = 0; i < N; i++) {
            T[N + i][0] = INF;
            T[N + i][1] = i + 1;
        }
        for (int i = N - 1; i > 0; i--) merge(i, i << 1, i << 1 | 1);
    }

    static void update(int i, int v) {
        for (T[i += N - 1][0] = v; (i >>= 1) > 0;) merge(i, i << 1, i << 1 | 1);
    }

    static int[] query(int l, int r) {
        T[0][0] = INF;
        T[0][1] = -1;
        for (l += N - 1, r += N - 1; l <= r; l >>= 1, r >>= 1) {
            if ((l & 1) == 1) merge(0, 0, l++);
            if ((r & 1) == 0) merge(0, 0, r--);
        }
        return T[0];
    }
    
    public static void run(int testCaseNum) throws Exception {
        N = in.nextInt();
        A = new int[N + 1];
        queries = new ArrayList[N + 1];
        ind = new int[MAXA];
        for (int i = 1; i <= N; i++) {
            A[i] = in.nextInt();
            queries[i] = new ArrayList<int[]>();
        }
        for (int i = 0; i < MAXA; i++) ind[i] = -1;
        Q = in.nextInt();
        ans = new int[Q];
        for (int i = 0; i < Q; i++) {
            int l = in.nextInt(), r = in.nextInt();
            queries[r].add(new int[]{l, i});
        }
        build();
        for (int i = 1; i <= N; i++) {
            if (ind[A[i]] != -1) update(ind[A[i]], INF);
            update(i, ind[A[i]]);
            ind[A[i]] = i;
            for (int[] q : queries[i]) {
                int[] res = query(q[0], i);
                if (res[0] < q[0]) ans[q[1]] = A[res[1]];
            }
        }
        for (int i = 0; i < Q; i++) out.println(ans[i]);
    }
}
