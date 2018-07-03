import java.io.*;
import java.math.*;
import java.util.*;

public class DS4_Sqrt_Array {
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
            c = read();
            while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1) c = read();
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
            while ((c = read()) != -1) {
                if (c == '\n' || c == '\r') break;
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
    
    public static int FACTOR = 4;
    
    public static ArrayList<ArrayList<Integer>> a;
    public static ArrayList<Integer> prefixSZ;
    public static int n;
    
    public static void init (ArrayList<Integer> b) {
        n = N;
        a = new ArrayList<ArrayList<Integer>>();
        prefixSZ = new ArrayList<Integer>();
        int sqrtn = (int) Math.sqrt(n) * FACTOR;
        for (int i = 0; i < b.size(); i += sqrtn) {
            a.add(new ArrayList<Integer>(b.subList(i, Math.min(i + sqrtn, b.size()))));
            prefixSZ.add(i);
        }
    }
    
    public static void insert(int val) {
        int lo = 0, hi = a.size(), mid, midSZ;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            midSZ = a.get(mid).size();
            if (val < a.get(mid).get(midSZ - 1)) hi = mid;
            else lo = mid + 1;
        }
        int i = lo;
        ArrayList<Integer> ai;
        if (lo != a.size()) {
            ai = a.get(i);
            lo = 0;
            hi = ai.size();
            while (lo < hi) {
                mid = lo + (hi - lo) / 2;
                if (val < ai.get(mid)) hi = mid;
                else lo = mid + 1;
            }
        }
        if (n++ == 0) {
            a.add(new ArrayList<Integer>());
            prefixSZ.add(0);
        }
        ai = a.get(Math.min(i, a.size() - 1));
        if (i == a.size()) {
            i--;
            ai.add(val);
        } else ai.add(lo, val);
        int sqrtn = ((int) Math.sqrt(n)) * FACTOR;
        if (ai.size() > 2 * sqrtn) {
            a.add(i + 1, new ArrayList<Integer>(ai.subList(sqrtn, ai.size())));
            ai.subList(sqrtn, ai.size()).clear();
            prefixSZ.add(0);
        }
        for (int j = i + 1; j < a.size(); j++) prefixSZ.set(j, prefixSZ.get(j - 1) + a.get(j - 1).size());
    }
    
    public static void remove(int val) {
        int lo = 0, hi = a.size(), mid, midSZ;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            midSZ = a.get(mid).size();
            if (a.get(mid).get(midSZ - 1) < val) lo = mid + 1;
            else hi = mid;
        }
        if (lo == a.size()) return;
        int i = lo;
        ArrayList<Integer> ai = a.get(i);
        lo = 0;
        hi = ai.size();
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (ai.get(mid) < val) lo = mid + 1;
            else hi = mid;
        }
        if (ai.get(lo) != val) return;
        --n;
        ai.remove(lo);
        if (ai.isEmpty()) {
            a.remove(i);
            prefixSZ.remove(prefixSZ.size() - 1);
        }
        for (int j = i + 1; j < a.size(); j++) prefixSZ.set(j, prefixSZ.get(j - 1) + a.get(j - 1).size());
    }
    
    public static int get(int k) {
        int lo = 0, hi = a.size() - 1, mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (k < prefixSZ.get(mid)) hi = mid - 1;
            else lo = mid + 1;
        }
        return a.get(hi).get(k - prefixSZ.get(hi));
    }
    
    public static int getRank(int val) {
        int lo = 0, hi = a.size(), mid, midSZ;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            midSZ = a.get(mid).size();
            if (a.get(mid).get(midSZ - 1) < val) lo = mid + 1;
            else hi = mid;
        }
        if (lo == a.size()) return -1;
        int i = lo;
        ArrayList<Integer> ai = a.get(i);
        lo = 0;
        hi = ai.size();
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (ai.get(mid) < val) lo = mid + 1;
            else hi = mid;
        }
        return a.get(i).get(lo) == val ? prefixSZ.get(i) + lo : -1;
    }
    
    public static void print() {
        for (ArrayList<Integer> b : a) for (int x : b) out.print(x + " ");
    }

    public static int N, M;
    public static int[] A;
    
    public static void run(int testCaseNum) throws Exception {
        in.setLength(5);
        N = in.nextInt();
        M = in.nextInt();
        A = new int[N];
        for (int i = 0; i < N; i++) A[i] = in.nextInt();
        Arrays.sort(A);
        ArrayList<Integer> b = new ArrayList<Integer>(N);
        for (int i = 0; i < N; i++) b.add(A[i]);
        init(b);
        int lastAns = 0;
        for (int i = 0; i < M; i++) {
            char op = in.nextChar();
            int x = in.nextInt() ^ lastAns;
            if (op == 'I') {
                insert(x);
            } else if (op == 'R') {
                remove(x);
            } else if (op == 'S') {
                lastAns = get(x - 1);
                out.println(lastAns);
            } else if (op == 'L') {
                int k = getRank(x);
                lastAns = k == -1 ? -1 : k + 1;
                out.println(lastAns);
            } else {
                i--;
            }
        }
        print();
        out.println();
    }
}