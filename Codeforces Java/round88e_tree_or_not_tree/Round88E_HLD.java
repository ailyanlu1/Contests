// http://codeforces.com/contest/117/problem/E
import java.io.*;
import java.math.*;
import java.util.*;

public class Round88E_HLD {
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

    static int N, H, M, chainNum = 0, curInd = 1, cycleStart, cycleCnt = 0;
    static ArrayList<Integer>[] adj, adj2;
    static int[] dep, par, par2, chain, sz, head, ind, vert, T;
    static boolean[] vis, inCycle, L;

    static void dfs1(int v, int prev) {
        vis[v] = true;
        for (int w : adj[v]) {
            if (w == prev) continue;
            if (vis[w]) cycleStart = w;
            else dfs1(w, v);
        }
    }

    static boolean dfs2(int v, int prev) {
        vis[v] = true;
        for (int w : adj[v]) {
            if (w == prev) continue;
            if (vis[w] || dfs2(w, v)) {
                inCycle[v] = true;
                ind[v] = curInd;
                vert[curInd++] = v;
                cycleCnt++;
                return true;
            }
        }
        return false;
    }

    static void dfs3(int v, int d, int prev) {
        dep[v] = d;
        par2[v] = prev;
        sz[v] = 1;
        for (int w : adj2[v]) {
            if (w == prev) continue;
            dfs3(w, d + 1, v);
            sz[v] += sz[w];
        }
    }

    static void hld(int v, int prev) {
        if (head[chainNum] == -1) head[chainNum] = v;
        chain[v] = chainNum;
        if (v != cycleStart) {
            ind[v] = curInd;
            vert[curInd++] = v;
        }
        int maxInd = -1;
        for (int w : adj2[v]) if (w != prev && (maxInd == -1 || sz[maxInd] < sz[w])) maxInd = w;
        if (maxInd != -1) hld(maxInd, v);
        for (int w : adj2[v]) {
            if (w == prev || w == maxInd) continue;
            chainNum++;
            hld(w, v);
        }
    }

    static void apply(int i, int k) {
        T[i] = k - T[i];
        if (i < N) L[i] ^= true;
    }

    static int eval(int i, int k) {
        return L[i] ? k - (T[i << 1] + T[i << 1 | 1]) : T[i << 1] + T[i << 1 | 1];
    }

    static void pushup(int i) {
        for (int k = 2; i > 1; k <<= 1) {
            i >>= 1;
            T[i] = eval(i, k);
        }
    }

    static void propagate(int i) {
        for (int h = H, k = 1 << (H - 1); h > 0; h--, k >>= 1) {
            int ii = i >> h;
            if (L[ii]) {
                apply(ii << 1, k);
                apply(ii << 1 | 1, k);
                L[ii] = false;
            }
        }
    }

    static void build() {
        T = new int[2 * N];
        L = new boolean[N];
        H = 0;
        for (int i = 1; i <= N; H++) i <<= 1;
        for (int i = 0; i < N; i++) {
            T[N + i] = 1;
            L[i] = false;
        }
        for (int i = N - 1; i > 0; i--) T[i] = T[i << 1] + T[i << 1 | 1];
    }

    static void update(int l, int r) {
        if (l > r) return;
        l += N - 1;
        r += N - 1;
        propagate(l);
        propagate(r);
        int l0 = l, r0 = r, k = 1;
        for (; l <= r; l >>= 1, r >>= 1, k <<= 1) {
            if ((l & 1) == 1) apply(l++, k);
            if ((r & 1) == 0) apply(r--, k);
        }
        pushup(l0);
        pushup(r0);
    }

    static int query(int l, int r) {
        if (l > r) return 0;
        l += N - 1;
        r += N - 1;
        propagate(l);
        propagate(r);
        int ret = 0;
        for (; l <= r; l >>= 1, r >>= 1) {
            if ((l & 1) == 1) ret += T[l++];
            if ((r & 1) == 0) ret += T[r--];
        }
        return ret;
    }

    static int lca(int v, int w) {
        while (chain[v] != chain[w]) {
            if (dep[head[chain[v]]] < dep[head[chain[w]]]) w = par2[head[chain[w]]];
            else v = par2[head[chain[v]]];
        }
        if (dep[v] < dep[w]) return v;
        return w;
    }

    static void updateCycle(int v, int w) {
        if (!inCycle[v] || !inCycle[w]) throw new RuntimeException();
        int vw = (ind[w] - ind[v] + cycleCnt) % cycleCnt, wv = (ind[v] - ind[w] + cycleCnt) % cycleCnt;
        if (vw > wv || (vw == wv && vert[(ind[v]) % cycleCnt + 1] > vert[(ind[v] + cycleCnt - 2) % cycleCnt + 1])) {
            int temp = v;
            v = w;
            w = temp;
        }
        if (ind[v] <= ind[w]) update(ind[v], ind[w] - 1);
        else {
            update(ind[v], cycleCnt);
            update(1, ind[w] - 1);
        }
    }

    static int updateUp(int v, int w) {
        int last = w;
        while (chain[v] != chain[w]) {
            update(ind[head[chain[v]]], ind[v]);
            last = head[chain[v]];
            v = par2[last];
        }
        if (v == w) return last;
        update(ind[w] + 1, ind[v]);
        return vert[ind[w] + 1];
    }

    static void updatePath(int v, int w) {
        int v1 = inCycle[v] ? cycleStart : v, w1 = inCycle[w] ? cycleStart : w;
        int lcaVert = lca(v1, w1);
        int v2 = updateUp(v1, lcaVert);
        int w2 = updateUp(w1, lcaVert);
        if (inCycle[lcaVert]) updateCycle(inCycle[v2] ? v : par[v2], inCycle[w2] ? w : par[w2]);
    }

    public static void run(int testCaseNum) throws Exception {
        N = in.nextInt();
        M = in.nextInt();
        adj = new ArrayList[N];
        adj2 = new ArrayList[N];
        vis = new boolean[N];
        inCycle = new boolean[N];
        dep = new int[N];
        par = new int[N];
        par2 = new int[N];
        chain = new int[N];
        sz = new int[N];
        head = new int[N];
        ind = new int[N];
        vert = new int[N + 1];
        for (int i = 0; i < N; i++) {
            adj[i] = new ArrayList<Integer>();
            adj2[i] = new ArrayList<Integer>();
            head[i] = -1;
            vis[i] = false;
            inCycle[i] = false;
        }
        for (int i = 0; i < N; i++) {
            int a = in.nextInt() - 1, b = in.nextInt() - 1;
            adj[a].add(b);
            adj[b].add(a);
        }
        dfs1(0, -1);
        for (int i = 0; i < N; i++) vis[i] = false;
        dfs2(cycleStart, -1);
        for (int v = 0; v < N; v++) for (int w : adj[v]) if (!inCycle[v] || !inCycle[w]) adj2[inCycle[v] ? cycleStart : v].add(inCycle[w] ? cycleStart : w);
        dfs3(cycleStart, 0, -1);
        hld(cycleStart, -1);
        for (int v = 0; v < N; v++) for (int w : adj[v]) if (!inCycle[v] && inCycle[w]) par[v] = w;
        build();
        for (int i = 0; i < M; i++) {
            updatePath(in.nextInt() - 1, in.nextInt() - 1);
            out.println(Math.max(query(1, cycleCnt), 1) + query(cycleCnt + 1, N));
        }
    }
}
