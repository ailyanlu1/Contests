// https://www.spoj.com/problems/MAXCHILDSUM/
import java.io.*;
import java.math.*;
import java.util.*;

public class MAXCHILDSUM {
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
    
    static int N, H, Q, curInd, chainNum;
    static ArrayList<Integer>[] adj;
    static int[] depth, parent, size, head, chain, pre, post;
    static long[] T, L;
    static int[][] queries;
    
    static void apply(int i, long v) {
        T[i] += v;
        if (i < N) L[i] += v;
    }
    
    static void pushup(int i) {
        while (i > 1) {
            i >>= 1;
            T[i] = Math.max(T[i << 1], T[i << 1 | 1]) + L[i];
        }
    }
    
    static void propagate(int i) {
        for (int h = H; h > 0; h--) {
            int ii = i >> h;
            if (L[ii] != 0) {
                apply(ii << 1, L[ii]);
                apply(ii << 1 | 1, L[ii]);
                L[ii] = 0;
            }
        }
    }
    
    static void init() {
        T = new long[2 * N];
        L = new long[N];
        H = 0;
        for (int i = 1; i <= N; H++) i <<= 1;
        for (int i = 1; i < 2 * N; i++) T[i] = 0;
        for (int i = 1; i < N; i++) L[i] = 0;
    }
    
    static void update(int l, int r, long v) {
        l += N - 1;
        r += N - 1;
        propagate(l);
        propagate(r);
        int l0 = l, r0 = r;
        for (; l <= r; l >>= 1, r >>= 1) {
            if ((l & 1) == 1) apply(l++, v);
            if ((r & 1) == 0) apply(r--, v);
        }
        pushup(l0);
        pushup(r0);
    }
    
    static long query(int l, int r) {
        if (l > r) return 0;
        l += N - 1;
        r += N - 1;
        propagate(l);
        propagate(r);
        long ret = 0;
        for (; l <= r; l >>= 1, r >>= 1) {
            if ((l & 1) == 1) ret = Math.max(ret, T[l++]);
            if ((r & 1) == 0) ret = Math.max(ret, T[r--]);
        }
        return ret;
    }
    
    static void dfs(int v) {
        size[v] = 1;
        for (int w : adj[v]) {
            parent[w] = v;
            depth[w] = depth[v] + 1;
            dfs(w);
            size[v] += size[w];
        }
    }
    static void hld(int v) {
        if (head[chainNum] == -1) head[chainNum] = v;
        chain[v] = chainNum;
        pre[v] = ++curInd;
        int maxIndex = -1;
        for (int w : adj[v]) if (maxIndex == -1 || size[maxIndex] < size[w]) maxIndex = w;
        if (maxIndex != -1) hld(maxIndex);
        for (int w : adj[v]) {
            if (w == maxIndex) continue;
            chainNum++;
            hld(w);
        }
        post[v] = curInd;
    }
    
    static void updatePathToRoot(int v, long val) {
        while (chain[v] != chain[0]) {
            update(pre[head[chain[v]]], pre[v], val);
            v = parent[head[chain[v]]];
        }
        update(pre[0], pre[v], val);
    }
    
    static long querySubtree(int v) {
        return query(pre[v] + 1, post[v]);
    }
    
    public static void run(int testCaseNum) throws Exception {
        N = 1;
        Q = in.nextInt();
        queries = new int[Q][3];
        adj = new ArrayList[Q];
        for (int i = 0; i < Q; i++) adj[i] = new ArrayList<Integer>();
        for (int i = 0; i < Q; i++) {
            queries[i][0] = in.nextInt();
            if (queries[i][0] == 1) {
                adj[in.nextInt() - 1].add(N);
                queries[i][1] = N++;
                queries[i][2] = in.nextInt();
            } else {
                queries[i][1] = in.nextInt() - 1;
            }
        }
        curInd = chainNum = 0;
        depth = new int[N];
        parent = new int[N];
        size = new int[N];
        head = new int[N];
        chain = new int[N];
        pre = new int[N];
        post = new int[N];
        depth[0] = 0;
        parent[0] = -1;
        for (int i = 0; i < N; i++) head[i] = -1;
        dfs(0);
        hld(0);
        init();
        for (int i = 0; i < Q; i++) {
            if (queries[i][0] == 1) updatePathToRoot(queries[i][1], queries[i][2]);
            else out.println(querySubtree(queries[i][1]));
        }
    }
}
