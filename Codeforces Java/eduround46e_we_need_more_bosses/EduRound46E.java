// http://codeforces.com/contest/1000/problem/E
import java.io.*;
import java.math.*;
import java.util.*;

public class EduRound46E {
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
    
    static int N, M, cnt, curId;
    static int[] pre, low;
    static boolean[] vis;
    static ArrayList<int[]>[] adj;
    static ArrayList<Integer>[] adj2;
    
    static int dfs(int v, int prev) {
        int bridges = 0;
        pre[v] = low[v] = cnt++;
        for (int[] e : adj[v]) {
            if (pre[e[0]] == -1) {
                bridges += dfs(e[0], v);
                low[v] = Math.min(low[v], low[e[0]]);
                if (low[e[0]] == pre[e[0]]) {
                    e[1] = 1;
                    bridges++;
                }
            } else if (e[0] != prev && pre[e[0]] < low[v]) {
                low[v] = pre[e[0]];
            }
        }
        return bridges;
    }
    
    static void dfs2(int v, int prev, int vId) {
        vis[v] = true;
        for (int[] e : adj[v]) {
            if (vis[e[0]]) continue;
            if (e[1] == 1) {
                adj2[vId].add(++curId);
                adj2[curId].add(vId);
                dfs2(e[0], v, curId);
            } else {
                dfs2(e[0], v, vId);
            }
        }
    }

    static int[] dfs3(int v, int prev, int d) {
        int[] ret = new int[]{d, v};
        for (int w : adj2[v]) {
            if (w == prev) continue;
            int[] p = dfs3(w, v, d + 1);
            if (p[0] > ret[0]) ret = p;
        }
        return ret;
    }
    
    public static void run(int testCaseNum) throws Exception {
        N = in.nextInt();
        M = in.nextInt();
        adj = new ArrayList[N];
        pre = new int[N];
        low = new int[N];
        vis = new boolean[N];
        for (int i = 0; i < N; i++) {
            adj[i] = new ArrayList<int[]>();
            pre[i] = low[i] = -1;
            vis[i] = false;
        }
        for (int i = 0; i < M; i++) {
            int a = in.nextInt() - 1, b = in.nextInt() - 1;
            adj[a].add(new int[]{b, 0});
            adj[b].add(new int[]{a, 0});
        }
        cnt = curId = 0;
        int compCnt = dfs(0, 0) + 1;
        adj2 = new ArrayList[compCnt];
        for (int i = 0; i < compCnt; i++) adj2[i] = new ArrayList<Integer>();
        dfs2(0, 0, 0);
        int[] furthest = dfs3(0, 0, 0);
        furthest = dfs3(furthest[1], furthest[1], 0);
        out.println(furthest[0]);
    }
}
