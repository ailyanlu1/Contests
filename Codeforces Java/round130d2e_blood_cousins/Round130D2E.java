// http://codeforces.com/contest/208/problem/E
import java.io.*;
import java.math.*;
import java.util.*;

public class Round130D2E {
    private static Round130D2E o = new Round130D2E();
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

        public byte nextByte() throws IOException {
            byte ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret *= 10;
                ret += c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg) return (byte) (-ret);
            return ret;
        }
        
        public short nextShort() throws IOException {
            short ret = 0;
            byte c = read();
            while (c <= ' ') c = read();
            boolean neg = (c == '-');
            if (neg) c = read();
            do {
                ret *= 10;
                ret += c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg) return (short) (-ret);
            return ret;
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
        
        public float nextFloat() throws IOException {
            float ret = 0, div = 1;
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
        String packageName = "";
        if (!stdIn || !stdOut) {
            try {
                packageName = o.getClass().getPackage().toString().split(" ")[1] + "/";
            } catch (NullPointerException e) {}
        }
        if (stdIn) in = new Reader(System.in);
        else in = new Reader(packageName + INPUT_FILE_NAME);
        if (stdOut) out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        else out = new PrintWriter(new BufferedWriter(new FileWriter(packageName + OUTPUT_FILE_NAME)));
        
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
    
    static int N, LGN, M;
    static int[] size, dep, cnt, ans;
    static int[][] par;
    static boolean[] isHeavy;
    static ArrayList<Integer>[] adj;
    static ArrayList<int[]>[] queries;

    static void getSize(int v, int prev, int d) {
        size[v] = 1;
        dep[v] = d;
        for (int w : adj[v]) {
            if (w == prev) continue;
            getSize(w, v, d + 1);
            size[v] += size[w];
        }
    }

    static void add(int v, int prev, int delta) {
        cnt[dep[v]] += delta;
        for (int w : adj[v]) if (w != prev && !isHeavy[w]) add(w, v, delta);
    }

    static void dfs(int v, int prev, boolean keep) {
        int maxSize = -1, heavyInd = -1;
        for (int w : adj[v]) {
            if (w != prev && size[w] > maxSize) {
                maxSize = size[w];
                heavyInd = w;
            }
        }
        for (int w : adj[v]) if (w != prev && w != heavyInd) dfs(w, v, false);
        if (heavyInd != -1) {
            dfs(heavyInd, v, true);
            isHeavy[heavyInd] = true;
        }
        add(v, prev, 1);
        for (int[] q : queries[v]) ans[q[1]] = dep[v] + q[0] >= N ? 0 : Math.max(cnt[dep[v] + q[0]] - 1, 0);
        if (heavyInd != -1) isHeavy[heavyInd] = false;
        if (!keep) add(v, prev, -1);
    }
    
    // TODO CODE GOES IN THIS METHOD
    public static void run(int testCaseNum) throws Exception {
        N = in.nextInt() + 1;
        LGN = (int) (Math.ceil(Math.log(N) / Math.log(2)) + 1);
        size = new int[N];
        dep = new int[N];
        cnt = new int[N];
        par = new int[N][LGN];
        isHeavy = new boolean[N];
        adj = new ArrayList[N];
        queries = new ArrayList[N];
        for (int i = 0; i < N; i++) {
            adj[i] = new ArrayList<Integer>();
            queries[i] = new ArrayList<int[]>();
            isHeavy[i] = false;
            cnt[i] = 0;
        }
        par[0][0] = -1;
        for (int i = 1; i < N; i++) {
            par[i][0] = in.nextInt();
            adj[par[i][0]].add(i);
        }
        getSize(0, -1, 0);
        for (int j = 1; j < LGN; j++) {
            for (int i = 0; i < N; i++) {
                if (par[i][j - 1] != -1) par[i][j] = par[par[i][j - 1]][j - 1];
            }
        }
        M = in.nextInt();
        ans = new int[M];
        for (int i = 0; i < M; i++) {
            int v = in.nextInt();
            int p = in.nextInt();
            if (dep[v] <= p) {
                ans[i] = 0;
            } else {
                int target = dep[v] - p;
                for (int j = LGN - 1; j >= 0; j--) {
                    if (par[v][j] != -1 && dep[par[v][j]] >= target) {
                        v = par[v][j];
                    }
                }
                queries[v].add(new int[] { p, i });
            }
        }
        dfs(0, -1, false);
        for (int i = 0; i < M; i++) out.print(ans[i] + " ");
        out.println();
    }
}
