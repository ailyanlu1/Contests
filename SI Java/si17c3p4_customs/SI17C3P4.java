import java.io.*;
import java.math.*;
import java.util.*;

public class SI17C3P4 {
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
    
    static final long MOD = (long) (1e9 + 7);
    
    static int N, M;
    static ArrayList<Integer>[] adj;
    static int cnt;
    static int[] pre, low;
    static ArrayList<HashSet<Integer>> components;
    static ArrayList<Integer> edgeCnt;
    static Stack<int[]> s;
    
    static void dfs(int v, int prev) {
        int children = 0;
        pre[v] = low[v] = cnt++;
        for (int w : adj[v]) {
            if (pre[w] == -1) {
                children++;
                s.push(new int[]{v, w});
                dfs(w, v);
                low[v] = Math.min(low[v], low[w]);
                if ((prev == v && children > 1) || (prev != v && low[w] >= pre[v])) {
                    components.add(new HashSet<Integer>());
                    int numEdges = 0;
                    while (s.peek()[0] != v && s.peek()[1] != w) {
                        components.get(components.size() - 1).add(s.peek()[0]);
                        components.get(components.size() - 1).add(s.peek()[1]);
                        numEdges++;
                        s.pop();
                    }
                    components.get(components.size() - 1).add(s.peek()[0]);
                    components.get(components.size() - 1).add(s.peek()[1]);
                    numEdges++;
                    s.pop();
                    edgeCnt.add(numEdges);
                }
            } else if (w != prev && pre[w] < low[v]) {
                low[v] = pre[w];
                s.push(new int[]{v, w});
            }
        }
    }
    
    static void biconnected() {
        cnt = 0;
        low = new int[N];
        pre = new int[N];
        components = new ArrayList<HashSet<Integer>>();
        edgeCnt = new ArrayList<Integer>();
        s = new Stack<int[]>();
        for (int v = 0; v < N; v++) low[v] = pre[v] = -1;
        if (pre[0] == -1) dfs(0, 0);
        if (!s.isEmpty()) {
            components.add(new HashSet<Integer>());
            int numEdges = 0;
            while (!s.isEmpty()) {
                components.get(components.size() - 1).add(s.peek()[0]);
                components.get(components.size() - 1).add(s.peek()[1]);
                numEdges++;
                s.pop();
            }
            edgeCnt.add(numEdges);
        }
    }
    
    public static void run(int testCaseNum) throws Exception {
        N = in.nextInt();
        M = in.nextInt();
        adj = new ArrayList[N];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<Integer>();
        for (int i = 0; i < M; i++) {
            int a = in.nextInt() - 1, b = in.nextInt() - 1;
            adj[a].add(b);
            adj[b].add(a);
        }
        biconnected();
        for (int i = 0; i < N; i++) {
            if (pre[i] == -1) {
                out.println("safe");
                return;
            }
        }
        long ans = 1;
        for (int i = 0; i < components.size(); i++) {
            if (components.get(i).size() < edgeCnt.get(i)) {
                out.println("safe");
                return;
            }
            ans = (ans * edgeCnt.get(i)) % MOD;
        }
        out.println(ans);
    }
}
