import java.io.*;
import java.math.*;
import java.util.*;

public class Round88E_LCT {
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
    static ArrayList<Integer>[] adj;
    static int[] branch, ind, vert, T, L, R, P, VAL, SUM, SZ;
    static boolean[] vis, inCycle, TL, LZ;

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
    
    static void dfs3(int v, int prev, int curBranch) {
        vis[v] = true;
        if (inCycle[v]) curBranch = v;
        branch[v] = curBranch;
        for (int w : adj[v]) {
            if (w == prev || vis[w]) continue;
            dfs3(w, v, curBranch);
            if (!inCycle[v] || !inCycle[w]) link(inCycle[w] ? cycleStart : w, inCycle[v] ? cycleStart : v);
        }
    }

    static void apply(int i, int k) {
        T[i] = k - T[i];
        if (i < N) TL[i] ^= true;
    }

    static int eval(int i, int k) {
        return TL[i] ? k - (T[i << 1] + T[i << 1 | 1]) : T[i << 1] + T[i << 1 | 1];
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
            if (TL[ii]) {
                apply(ii << 1, k);
                apply(ii << 1 | 1, k);
                TL[ii] = false;
            }
        }
    }

    static void build() {
        T = new int[2 * N];
        TL = new boolean[N];
        H = 0;
        for (int i = 1; i <= N; H++) i <<= 1;
        for (int i = 0; i < N; i++) {
            T[N + i] = 1;
            TL[i] = false;
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

    static int applyLCT(int v, boolean lz, int sz) {
        return lz ? sz - v : v;
    }
    
    static int size(int x) {
        return x == -1 ? 0 : SZ[x];
    }
    
    static int sum(int x) {
        return x == -1 ? 0 : SUM[x];
    }
    
    static boolean isRoot(int x) {
        return P[x] == -1 || (x != L[P[x]] && x != R[P[x]]);
    }

    static void propagateLCT(int x) {
        if (LZ[x]) {
            VAL[x] = applyLCT(VAL[x], LZ[x], 1);
            SUM[x] = applyLCT(SUM[x], LZ[x], SZ[x]);
            LZ[x] ^= true;
            if (L[x] != -1) LZ[L[x]] ^= true;
            if (R[x] != -1) LZ[R[x]] ^= true;
        }
    }

    static void updateLCT(int x) {
        SUM[x] = applyLCT(VAL[x], LZ[x], 1);
        if (L[x] != -1) SUM[x] += applyLCT(SUM[L[x]], LZ[L[x]], SZ[L[x]]);
        if (R[x] != -1) SUM[x] += applyLCT(SUM[R[x]], LZ[R[x]], SZ[R[x]]);
        SZ[x] = 1 + size(L[x]) + size(R[x]);
    }

    static void connect(int ch, int par, boolean hasCh, boolean isL) {
        if (ch != -1) P[ch] = par;
        if (hasCh) {
            if (isL) L[par] = ch;
            else R[par] = ch;
        }
    }

    static void rotate(int x) {
        int p = P[x];
        int g = P[p];
        boolean isRootP = isRoot(p);
        boolean isL = x == L[p];
        connect(isL ? R[x] : L[x], p, true, isL);
        connect(p, x, true, !isL);
        connect(x, g, !isRootP, isRootP ? false : p == L[g]);
        updateLCT(p);
    }

    static void splay(int x) {
        while (!isRoot(x)) {
            int p = P[x];
            int g = P[p];
            if (!isRoot(p)) propagateLCT(g);
            propagateLCT(p);
            propagateLCT(x);
            if (!isRoot(p)) rotate((x == L[p]) == (p == L[g]) ? p : x);
            rotate(x);
        }
        propagateLCT(x);
        updateLCT(x);
    }
    
    static int expose(int x) {
        int last = -1;
        for (int y = x; y != -1; y = P[y]) {
            splay(y);
            L[y] = last;
            last = y;
        }
        splay(x);
        return last;
    }
    
    static void link(int x, int y) {
        expose(x);
        P[x] = y;
    }
    
    static int updatePathFromRoot(int x) {
        expose(x);
        int old = sum(x);
        LZ[x] ^= true;
        propagateLCT(x);
        return sum(x) - old;
    }
    
    static void initLCT() {
        L = new int[N];
        R = new int[N];
        P = new int[N];
        VAL = new int[N];
        SUM = new int[N];
        SZ = new int[N];
        LZ = new boolean[N];
        for (int i = 0; i < N; i++) {
            SZ[i] = SUM[i] = VAL[i] = 1;
            LZ[i] = false;
            L[i] = R[i] = P[i] = -1;
        }
    }

    public static void run(int testCaseNum) throws Exception {
        N = in.nextInt();
        M = in.nextInt();
        adj = new ArrayList[N];
        branch = new int[N];
        vis = new boolean[N];
        inCycle = new boolean[N];
        ind = new int[N];
        vert = new int[N + 1];
        initLCT();
        for (int i = 0; i < N; i++) {
            adj[i] = new ArrayList<Integer>();
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
        for (int i = 0; i < N; i++) vis[i] = false;
        dfs3(cycleStart, -1, -1);
        build();
        updatePathFromRoot(cycleStart);
        int lctCnt = N - cycleCnt;
        for (int i = 0; i < M; i++) {
            int a = in.nextInt() - 1, b = in.nextInt() - 1;
            lctCnt += updatePathFromRoot(inCycle[a] ? cycleStart : a) + updatePathFromRoot(inCycle[b] ? cycleStart : b);
            if (branch[a] != branch[b]) updateCycle(branch[a], branch[b]);
            out.println(Math.max(query(1, cycleCnt), 1) + lctCnt);
        }
    }
}
