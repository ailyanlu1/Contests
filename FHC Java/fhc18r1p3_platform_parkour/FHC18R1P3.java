// https://www.facebook.com/hackercup/problem/1892930427431211/
import java.io.*;
import java.math.*;
import java.util.*;

public class FHC18R1P3 {
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
    private static final String INPUT_FILE_NAME = "platform_parkour.txt";
    private static final String OUTPUT_FILE_NAME = "platform_parkour_out.txt";
    
    private static boolean stdIn = false;
    private static boolean stdOut = false;
    private static boolean crash = true;
    private static boolean flush = false;
    
    public static void main(String[] args) throws Exception {
        if (stdIn) in = new Reader(System.in);
        else in = new Reader(INPUT_FILE_NAME);
        if (stdOut) out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        else out = new PrintWriter(new BufferedWriter(new FileWriter(OUTPUT_FILE_NAME)));
        NUM_OF_TEST_CASES = in.nextInt();
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

    public static class IndexMinPQ<Key extends Comparable<Key>> implements Iterable<Integer> {
        private int maxN;        // maximum number of elements on PQ
        private int n;           // number of elements on PQ
        private int[] pq;        // binary heap using 1-based indexing
        private int[] qp;        // inverse of pq - qp[pq[i]] = pq[qp[i]] = i
        private Key[] keys;      // keys[i] = priority of i

        public IndexMinPQ(int maxN) {
            if (maxN < 0) throw new IllegalArgumentException();
            this.maxN = maxN;
            n = 0;
            keys = (Key[]) new Comparable[maxN];
            pq   = new int[maxN + 1];
            qp   = new int[maxN];
            for (int i = 0; i < maxN; i++)
                qp[i] = -1;
        }

        public boolean isEmpty() {
            return n == 0;
        }

        public boolean contains(int i) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            return qp[i] != -1;
        }

        public int size() {
            return n;
        }

        public void insert(int i, Key key) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (contains(i)) throw new IllegalArgumentException("index is already in the priority queue");
            n++;
            qp[i] = n;
            pq[n] = i;
            keys[i] = key;
            swim(n);
        }

        public int minIndex() {
            if (n == 0) throw new NoSuchElementException("Priority queue underflow");
            return pq[1];
        }

        public Key minKey() {
            if (n == 0) throw new NoSuchElementException("Priority queue underflow");
            return keys[pq[1]];
        }

        public int delMin() {
            if (n == 0) throw new NoSuchElementException("Priority queue underflow");
            int min = pq[1];
            exch(1, n--);
            sink(1);
            // assert min == pq[n+1];
            qp[min] = -1;        // delete
            keys[min] = null;    // to help with garbage collection
            pq[n+1] = -1;        // not needed
            return min;
        }

        public Key keyOf(int i) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            else return keys[i];
        }

        public void changeKey(int i, Key key) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            keys[i] = key;
            swim(qp[i]);
            sink(qp[i]);
        }

        public void decreaseKey(int i, Key key) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            if (keys[i].compareTo(key) <= 0)
                throw new IllegalArgumentException("Calling decreaseKey() with given argument would not strictly decrease the key");
            keys[i] = key;
            swim(qp[i]);
        }

        public void increaseKey(int i, Key key) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            if (keys[i].compareTo(key) >= 0)
                throw new IllegalArgumentException("Calling increaseKey() with given argument would not strictly increase the key");
            keys[i] = key;
            sink(qp[i]);
        }

        public void delete(int i) {
            if (i < 0 || i >= maxN) throw new IndexOutOfBoundsException();
            if (!contains(i)) throw new NoSuchElementException("index is not in the priority queue");
            int index = qp[i];
            exch(index, n--);
            swim(index);
            sink(index);
            keys[i] = null;
            qp[i] = -1;
        }

        private boolean greater(int i, int j) {
            return keys[pq[i]].compareTo(keys[pq[j]]) > 0;
        }

        private void exch(int i, int j) {
            int swap = pq[i];
            pq[i] = pq[j];
            pq[j] = swap;
            qp[pq[i]] = i;
            qp[pq[j]] = j;
        }

        private void swim(int k) {
            while (k > 1 && greater(k/2, k)) {
                exch(k, k/2);
                k = k/2;
            }
        }

        private void sink(int k) {
            while (2*k <= n) {
                int j = 2*k;
                if (j < n && greater(j, j+1)) j++;
                if (!greater(k, j)) break;
                exch(k, j);
                k = j;
            }
        }

        
        public Iterator<Integer> iterator() { 
            return new HeapIterator();
        }

        private class HeapIterator implements Iterator<Integer> {
            // create a new pq
            private IndexMinPQ<Key> copy;

            // add all elements to copy of heap
            // takes linear time since already in heap order so no keys move
            public HeapIterator() {
                copy = new IndexMinPQ<Key>(pq.length - 1);
                for (int i = 1; i <= n; i++)
                    copy.insert(pq[i], keys[pq[i]]);
            }

            public boolean hasNext()  { return !copy.isEmpty();                     }
            
            public void remove()      { throw new UnsupportedOperationException();  }

            public Integer next() {
                if (!hasNext()) throw new NoSuchElementException();
                return copy.delMin();
            }
        }
    }

    static long INF = 0x3f3f3f3f3f3f3f3fL;
    static double EPS = 1e-9;
    
    public static void run(int testCaseNum) throws Exception {
        int N = in.nextInt(), M = in.nextInt();
        long[] H = new long[N];
        H[0] = in.nextLong();
        H[1] = in.nextLong();
        long W = in.nextLong(), X = in.nextLong(), Y = in.nextLong(), Z = in.nextLong();
        for (int i = 2; i < N; i++) H[i] = (W * H[i - 2] + X * H[i - 1] + Y) % Z;
        int[] A = new int[M], B = new int[M];
        long[] U = new long[M], D = new long[M], dU = new long[N - 1], dD = new long[N - 1];
        ArrayList<Integer>[] stL = new ArrayList[N], enL = new ArrayList[N], stR = new ArrayList[N], enR = new ArrayList[N];
        for (int i = 0; i < N; i++) {
            stL[i] = new ArrayList<Integer>();
            enL[i] = new ArrayList<Integer>();
            stR[i] = new ArrayList<Integer>();
            enR[i] = new ArrayList<Integer>();
        }
        for (int i = 0; i < M; i++) {
            A[i] = in.nextInt() - 1;
            B[i] = in.nextInt() - 1;
            U[i] = in.nextLong();
            D[i] = in.nextLong();
            if (A[i] < B[i]) {
                stL[A[i]].add(i);
                enL[B[i]].add(i);
            } else {
                stR[A[i]].add(i);
                enR[B[i]].add(i);
            }
        }
        IndexMinPQ<Long> pqU = new IndexMinPQ<Long>(M), pqD = new IndexMinPQ<Long>(M);
        for (int i = 0; i < N - 1; i++) {
            for (int j : enL[i]) {
                pqU.delete(j);
                pqD.delete(j);
            }
            for (int j : stL[i]) {
                pqU.insert(j, U[j]);
                pqD.insert(j, D[j]);
            }
            if (pqU.isEmpty()) dU[i] = INF;
            else dU[i] = pqU.minKey();
            if (pqD.isEmpty()) dD[i] = INF;
            else dD[i] = pqD.minKey();
        }
        pqU = new IndexMinPQ<Long>(M);
        pqD = new IndexMinPQ<Long>(M);
        for (int i = N - 2; i >= 0; i--) {
            for (int j : enR[i + 1]) {
                pqU.delete(j);
                pqD.delete(j);
            }
            for (int j : stR[i + 1]) {
                pqU.insert(j, U[j]);
                pqD.insert(j, D[j]);
            }
            if (pqU.isEmpty()) dD[i] = Math.min(dD[i], INF);
            else dD[i] = Math.min(dD[i], pqU.minKey());
            if (pqD.isEmpty()) dU[i] = Math.min(dU[i], INF);
            else dU[i] = Math.min(dU[i], pqD.minKey());
        }
        long ans = 0;
        double lo = 0, hi = 1e9, mid;
        for (int it = 0; hi - lo > EPS && it < 300; it++) {
            mid = lo + (hi - lo) / 2;
            double lb = H[0] - mid, ub = H[0] + mid;
            boolean good = true;
            for (int i = 0; i < N - 1; i++) {
                if (ub + dU[i] < H[i + 1] - mid- EPS || H[i + 1] + mid < lb - dD[i] - EPS) {
                    good = false;
                    break;
                }
                lb = Math.max(lb - dD[i], H[i + 1] - mid);
                ub = Math.min(ub + dU[i], H[i + 1] + mid);
            }
            if (good) hi = mid;
            else lo = mid;
        }
        out.printf("Case #%d: %.6f\n", testCaseNum, lo);
    }
}
