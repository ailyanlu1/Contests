import java.io.*;
import java.math.*;
import java.util.*;

public class NCCO4D2P3 {
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
            int cnt = 0;
            byte c;
            do {
                c = read();
            } while (c <= ' ');
            do {
                buf[cnt++] = c;
            } while ((c = read()) > ' ');
            return new String(buf, 0, cnt);
        }

        public String nextLine() throws IOException {
            byte[] buf = new byte[LENGTH];
            int cnt = 0;
            byte c;
            do {
                c = read();
            } while (c <= ' ');
            do {
                buf[cnt++] = c;
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
                System.err.println("Exception thrown on test case " + i);
                e.printStackTrace(System.err);
                out.flush();
                if (crash) throw new Exception();
            }
            if (flush) out.flush();
        }
        in.close();
        out.close();
    }
    
    static int N, K;
    static int[] A;
    static long[] POW;
    
    static final long BASE = 10007L;
    static final long MOD = (long) (1e9 + 7);
    
    static boolean check(int L) {
        long hash = 0L;
        HashMap<Long, Integer> H = new HashMap<Long, Integer>();
        for (int i = 1; i <= N; i++) {
            hash = (hash * BASE + A[i]) % MOD;
            if (i >= L) {
                hash -= A[i - L] * POW[L] % MOD;
                if (hash < 0) hash += MOD;
                Integer x = H.get(hash);
                if (x == null) H.put(hash, 1);
                else {
                    if (x + 1 >= K) return true;
                    H.put(hash, x + 1);
                }
            }
        }
        return false;
    }
    
    // TODO CODE GOES IN THIS METHOD
    public static void run(int testCaseNum) throws Exception {
        N = in.nextInt();
        K = in.nextInt();
        A = new int[N + 1];
        POW = new long[N + 1];
        POW[0] = 1;
        for (int i = 1; i <= N; i++) {
            A[i] = in.nextInt();
            POW[i] = POW[i - 1] * BASE % MOD;
        }
        int lo = 1, hi = N, mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (check(mid)) lo = mid + 1;
            else hi = mid - 1;
        }
        out.println(lo - 1);
    }
}